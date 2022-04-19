/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:47:39 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/24 00:26:11 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_3(int *is_and, t_token *tmp)
{
	*is_and = 0;
	if (g_data->is_pipe == 0 && tmp->next
		&& what_im(tmp->next->cmd) == 3 && tmp->redirect.outfd == 1)
		redirect_exec(tmp, 1);
	else
		redirect_exec(tmp, 0);
}

void	execute_4(int *is_or, t_token *tmp)
{
	*is_or = 0;
	if (g_data->is_pipe == 0 && tmp->next
		&& what_im(tmp->next->cmd) == 3 && tmp->redirect.outfd == 1)
		redirect_exec(tmp, 1);
	else
		redirect_exec(tmp, 0);
}

void	execute_5(int *is_and, int *is_or, int start, t_token *tmp)
{
	if (start == 0 && what_im(tmp->cmd) == 1)
		*is_and = 1;
	else if (start == 0 && what_im(tmp->cmd) == 2)
		*is_or = 1;
}

void	execute_2(int *is_or, int *is_and, t_token *tmp, int start)
{
	if (*is_and == 1 && g_data->lastret == 0)
		execute_3(is_and, tmp);
	else if (*is_or == 1 && g_data->lastret != 0)
		execute_4(is_or, tmp);
	else if (start == 1 && g_data->is_pipe == 0 && tmp->next
		&& what_im(tmp->next->cmd) == 3 && tmp->redirect.outfd == 1)
		redirect_exec(tmp, 1);
	else if (start == 1)
		redirect_exec(tmp, 0);
}

void	execute(t_token *token)
{
	int		start;
	t_token	*tmp;
	int		is_and;
	int		is_or;
	int		is_ope;

	tmp = token;
	init(&start, &is_and, &is_or, &is_ope);
	while (tmp && g_data->hd_stop == 0)
	{
		init_2(tmp);
		if (what_im(tmp->cmd) == 0)
			execute_2(&is_or, &is_and, tmp, start);
		else
			execute_5(&is_and, &is_or, start, tmp);
		tmp = tmp->next;
		start = 0;
	}
}
