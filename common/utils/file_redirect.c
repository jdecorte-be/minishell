/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:33:24 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/08 19:30:32 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redirect_2_2(t_redirect *file)
{
	if (g_data->hd)
	{
		file->infd = g_data->hd->fd;
		g_data->hd = g_data->hd->next;
	}
}

void	open_infd(t_redirect *file, t_redirect *tmp, char *line, char *str)
{
	if (file->infd != tmp->infd)
		close(file->infd);
	if (file->open->fd == 0)
	{
		str = ft_redirect_chwc(ft_cut_chevron(file->infile->content));
		line = ft_ecrase_q(str);
		file->infd = open(line, O_RDONLY);
		free(str);
		free(line);
	}
	else if (file->open->fd == 1)
		ft_redirect_2_2(file);
	if (file->infd == -1)
		perror("open rd");
}

char	*ft_redirect_3_free(char *str, t_redirect *file)
{
	char	*ret;
	char	*tmp;

	tmp = ft_redirect_chwc(ft_cut_chevron(str));
	ret = ft_ecrase_q(tmp);
	if (!ft_chwc_ok2(file->outfile->content))
		free(tmp);
	return (ret);
}

void	ft_redirect_3_1(t_redirect *file, t_redirect *tmp, char *to_free)
{
	if (ft_chwc_ok2(file->outfile->content)
		|| ft_transf_int(file->outfile->content))
	{
		if (file->outfd != tmp->outfd)
			close(file->outfd);
		if (file->open2->fd == 0)
		{
			(to_free) = ft_redirect_3_free(file->outfile->content, file);
			file->outfd = open((to_free), O_WRONLY
					| O_TRUNC | O_CREAT, 0644);
			free((to_free));
		}
		else if (file->open2->fd == 1)
		{
			(to_free) = ft_redirect_3_free(file->outfile->content, file);
			file->outfd = open((to_free), O_WRONLY
					| O_APPEND | O_CREAT, 0644);
			free((to_free));
		}
		if (file->outfd == -1)
			perror("open wr");
	}
}

void	ft_redirect_3(t_redirect *file, t_redirect *tmp, char *to_free)
{
	if (ft_chwc_ok2(file->outfile->content)
		|| ft_transf_int(file->outfile->content))
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
