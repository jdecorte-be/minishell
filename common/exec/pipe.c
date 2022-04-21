/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:52:31 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/05/08 17:27:50 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_ope(t_token *tmp)
{
	int	ret;

	ret = 1;
	while (g_data->is_pipe && tmp->cmd)
	{
		init_2(tmp);
		if (g_data->is_pipe && tmp->next && what_im(tmp->next->cmd) == 3)
			ret = pipex(tmp->cmd);
		else if (g_data->is_pipe == 1 && what_im(tmp->cmd) == 0)
		{
			g_data->is_pipe = 0;
			if (tmp->redirect.outfd == -1 || tmp->redirect.infd == -1)
				return (1);
			dup2(tmp->redirect.infd, 0);
			dup2(tmp->redirect.outfd, 1);
			ret = exec(tmp->cmd);
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	exec_pipe(t_token *tmp)
{
	int	ret;

	ret = 0;
	if (tmp && what_im(tmp->cmd) == 0 && tmp->next
		&& what_im(tmp->next->cmd) == 3 && !tmp->next->next)
		printf("prohibited character or input not close\n");
	else
		ret = pipe_ope(tmp);
	return (ret);
}
