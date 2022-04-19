/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:33:24 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/12 19:31:29 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_redirect_check_2(t_list *tmp, char *c)
{
	*c = ft_strstrchr(tmp->content, "|&()");
	if (c != 0)
	{
		printf("bash: syntax error near unexpected token `%s'\n", c);
		return (0);
	}
	tmp = tmp->next;
	return (1);
}

int	ft_redirect_check(t_redirect file)
{
	t_list	*tmp;
	char	c;
	int		fd;

	tmp = file.infile;
	while (tmp)
	{
		if (!ft_redirect_check_2(tmp, &c))
			return (0);
	}
	tmp = file.outfile;
	while (tmp)
	{
		c = ft_strstrchr(tmp->content, "|&()");
		if (c != 0)
		{
			printf("bash: syntax error near unexpected token `%c'\n", c);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	ft_chrredirect_2(t_hd **open, t_hd **open2, int i)
{
	if (i == 0)
		ft_hdadd_back(open2, ft_hdnew(1));
	else if (i != 0)
		ft_hdadd_back(open2, ft_hdnew(0));
}

void	ft_chrredirect_3(t_hd **open, int i2)
{
	if (i2 == 0)
		ft_hdadd_back(open, ft_hdnew(1));
	else if (i2 != 0)
		ft_hdadd_back(open, ft_hdnew(0));
}

char	*ft_chrredirect(char *line, t_hd **open, t_hd **open2, size_t *v)
{
	size_t	end;
	size_t	start;
	int		i;
	int		i2;

	end = 0;
	i = 2;
	i2 = 2;
	if (line[end] == '<')
		while (line[end] == '<' && i2--)
			end++;
	else
		while (line[end] == '>' && i--)
			end++;
	ft_chrredirect_2(open, open2, i);
	ft_chrredirect_3(open, i2);
	while (ft_isspace(line[end]))
		end++;
	start = end;
	while (line[end] && !ft_isspace(line[end]))
		end++;
	*v = end;
	return (ft_substr(line, start, end - start));
}

t_list	*ft_file(char *line, char c, t_hd **open, t_hd **open2)
{
	t_list	*lst;
	size_t	i;
	char	*str;
	size_t	v;

	v = 0;
	lst = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] && ft_strchr("\'\"", line[i]))
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				i++;
			if (line[i])
				i++;
		}
		else if (line[i] && ft_strchr("(", line[i]) && ++i)
		{
			v = 1;
			while (line[i] && v != 0)
			{
				if (line[i] == '(')
					v++;
				else if (line[i] == ')')
					v--;
				i++;
			}
		}
		else if (line[i] && line[i] == c && line[i + 1])
		{
			v = 0;
			str = ft_chrredirect(line + i, open, open2, &v);
			ft_lstadd_back(&lst, ft_lstnew(str));
			i += v;
		}
		else if (line[i])
			i++;
	}
	return (lst);
}

t_redirect	ft_init_redirect(void)
{
	t_redirect	file;

	file.infile = 0;
	file.outfile = 0;
	file.infd = 0;
	file.outfd = 1;
	file.open = 0;
	file.open2 = 0;
	return (file);
}

t_redirect	ft_redirect(char *line, t_redirect file, int e, int fd)
{
	t_redirect	tmp;
	t_hd		*tmp2;
	char		*to_free;

	if (!line)
		return (file);
	tmp = file;
	file.infile = ft_file(line, '<', &file.open, &file.open2);
	file.outfile = ft_file(line, '>', &file.open, &file.open2);
	if (e)
	{
		if (e == 1)
			file.outfd = fd;
		else if (e == 2)
			file.infd = fd;
	}
	if (ft_redirect_check(file))
	{
		while (file.infile)
		{
			if (ft_chwc_ok2(file.infile->content)
				|| ft_transf(file.infile->content))
			{
				if (file.infd != tmp.infd)
					close(file.infd);
				if (file.open->fd == 0)
					file.infd = open(ft_ecrase_q(ft_redirect_chwc(ft_cut_chevron
									(file.infile->content))), O_RDONLY);
				else if (file.open->fd == 1)
				{
					if (g_data->hd)
					{
						file.infd = g_data->hd->fd;
						g_data->hd = g_data->hd->next;
					}
				}
				if (file.infd == -1)
					perror("open rd");
			}
			else
			{
				file.infd = -1;
				write(2, "minishell: *: ambiguous redirect\n", 33);
				g_data->lastret = 1;
			}
			file.infile = ft_next(file.infile);
			if (file.open2->next)
				file.open2 = file.open2->next;
		}
		while (file.outfile)
		{
			if (ft_chwc_ok2(file.outfile->content)
				|| ft_transf(file.outfile->content))
			{
				if (file.outfd != tmp.outfd)
					close(file.outfd);
				if (file.open2->fd == 0)
				{
					to_free = ft_ecrase_q(ft_redirect_chwc
							(ft_cut_chevron(file.outfile->content)));
					file.outfd = open(to_free, O_WRONLY
							| O_TRUNC | O_CREAT, 0644);
					free(to_free);
				}
				else if (file.open2->fd == 1)
				{
					to_free = ft_ecrase_q(ft_redirect_chwc
							(ft_cut_chevron(file.outfile->content)));
					file.outfd = open(to_free, O_WRONLY
							| O_APPEND | O_CREAT, 0644);
					free(to_free);
				}
				if (file.outfd == -1)
					perror("open wr");
			}
			else
			{
				file.outfd = -1;
				write(2, "minishell: *: ambiguous redirect\n", 33);
				g_data->lastret = 1;
			}
			file.outfile = ft_next(file.outfile);
			if (file.open->next)
				file.open = file.open->next;
		}
	}
	return (file);
}
