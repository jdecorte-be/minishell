/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   john_side.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:56:54 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/05 01:29:05 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_write_in_new_pipe(char *str)
{
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error(3);
	write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	return (fd[0]);
}

int	ft_hd_replace(int fd)
{
	char	*s1;
	char	*s2;

	s1 = 0;
	s2 = get_next_line(fd);
	while (s2)
	{
		s1 = ft_strjoin2(s1, s2);
		s2 = get_next_line(fd);
	}
	s2 = ft_chdollar_hd(s1);
	dup2(ft_write_in_new_pipe(s2), fd);
	return (fd);
}

void	ft_redirect_for_john(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (token->redirect.open && token->redirect.open->fd == 1)
		g_data->hd->fd = ft_hd_replace(g_data->hd->fd);
	token->redirect = ft_redirect(token->cmd, token->redirect, 0, 0);
	if (tmp->sub_token)
	{
		tmp = tmp->sub_token;
		while (tmp)
		{
			tmp->redirect = tmp->sup_token->redirect;
			tmp = tmp->next;
		}
	}
}
