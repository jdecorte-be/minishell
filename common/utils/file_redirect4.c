/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirect4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:27:22 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/05/09 22:31:19 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redirect_2(t_redirect *file, t_redirect *tmp, char *line, char *str)
{
	if (ft_chwc_ok2(file->infile->content)
		|| ft_transf_int(file->infile->content))
		open_infd(&file, tmp, line, str);
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

void	e_exist(t_redirect *file, int e, int fd)
{
	if (e == 1)
		file->outfd = fd;
	else if (e == 2)
		file->infd = fd;
}

t_redirect	ft_redirect(char *line, t_redirect file, int e, int fd)
{
	t_redirect	tmp;
	char		*to_free;
	char		*to_free2;

	to_free = NULL;
	to_free2 = NULL;
	if (!line)
		return (file);
	tmp = file;
	file.infile = ft_file(line, '<', &file.open, &file.open2);
	file.outfile = ft_file(line, '>', &file.open, &file.open2);
	if (e)
		e_exist(&file, e, fd);
	if (ft_redirect_check(file))
	{
		while (file.infile)
			ft_redirect_2(&file, &tmp, to_free, to_free2);
		while (file.outfile)
			ft_redirect_3(&file, &tmp, to_free);
	}
	return (file);
}
