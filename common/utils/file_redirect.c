/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:33:24 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/03 15:52:05 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_redirect_check_2(t_list *tmp, char *c);
int			ft_redirect_check(t_redirect file);
void		ft_chrredirect_2(t_hd **open, t_hd **open2, int i, int i2);
char		*ft_chrredirect(char *line, t_hd **open, t_hd **open2, size_t *v);

void		ft_file_2(size_t *v, char *line, size_t *i);
t_list		*ft_file(char *line, char c, t_hd **open, t_hd **open2);
t_redirect	ft_init_redirect(void);

void	ft_redirect_2_2(t_redirect *file)
{
	if (g_data->hd)
	{
		file->infd = g_data->hd->fd;
		g_data->hd = g_data->hd->next;
	}
}

void	ft_redirect_2(t_redirect *file, t_redirect *tmp, char *line)
{
	if (ft_chwc_ok2(file->infile->content) || ft_transf(file->infile->content))
	{
		if (file->infd != tmp->infd)
			close(file->infd);
		if (file->open->fd == 0)
			file->infd = open(ft_ecrase_q(ft_redirect_chwc(
							ft_cut_chevron(file->infile->content))), O_RDONLY);
		else if (file->open->fd == 1)
			ft_redirect_2_2(file);
		if (file->infd == -1)
			perror("open rd");
	}
	else
	{
		file->infd = -1;
		write(2, "minishell: *: ambiguous redirect\n", 33);
		g_data->lastret = 1;
	}
	file->infile = ft_next(file->infile);
	if (file->open2->next)
		file->open2 = file->open2->next;
}

void	ft_redirect_3_1(t_redirect *file, t_redirect *tmp, char **to_free)
{
	if (ft_chwc_ok2(file->outfile->content)
		|| ft_transf(file->outfile->content))
	{
		if (file->outfd != tmp->outfd)
			close(file->outfd);
		if (file->open2->fd == 0)
		{
			(*to_free) = ft_ecrase_q(ft_redirect_chwc
					(ft_cut_chevron(file->outfile->content)));
			file->outfd = open((*to_free), O_WRONLY
					| O_TRUNC | O_CREAT, 0644);
			free((*to_free));
		}
		else if (file->open2->fd == 1)
		{
			(*to_free) = ft_ecrase_q(ft_redirect_chwc
					(ft_cut_chevron(file->outfile->content)));
			file->outfd = open((*to_free), O_WRONLY
					| O_APPEND | O_CREAT, 0644);
			free((*to_free));
		}
		if (file->outfd == -1)
			perror("open wr");
	}
}

void	ft_redirect_3(t_redirect *file, t_redirect *tmp, char **to_free)
{
	if (ft_chwc_ok2(file->outfile->content)
		|| ft_transf(file->outfile->content))
		ft_redirect_3_1(file, tmp, to_free);
	else
	{
		file->outfd = -1;
		write(2, "minishell: *: ambiguous redirect\n", 33);
		g_data->lastret = 1;
	}
	file->outfile = ft_next(file->outfile);
	if (file->open->next)
		file->open = file->open->next;
}

t_redirect	ft_redirect(char *line, t_redirect file, int e, int fd)
{
	t_redirect	tmp;
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
			ft_redirect_2(&file, &tmp, line);
		while (file.outfile)
			ft_redirect_3(&file, &tmp, &to_free);
	}
	return (file);
}
