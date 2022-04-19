/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:49:05 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 18:12:19 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	what_im(char *input)
{
	if (ft_strcmp(input, "&&") == 0)
		return (1);
	else if (ft_strcmp(input, "||") == 0)
		return (2);
	else if (ft_strcmp(input, "|") == 0)
		return (3);
	else if (ft_strcmp(input, "<") == 0)
		return (4);
	else if (ft_strcmp(input, ">") == 0)
		return (5);
	else if (ft_strcmp(input, "(") == 0)
		return (4);
	else if (ft_strcmp(input, ")") == 0)
		return (5);
	return (0);
}

int	exec_pipe(t_token *tmp)
{
	int	ret;

	ret = 0;
	while (g_data->is_pipe && tmp->cmd)
	{
		tmp->cmd = ft_add_q_dollar(tmp->cmd);
		tmp->cmd = ft_chdollar(tmp->cmd);
		ft_redirect_for_john(tmp);
		tmp->cmd = ft_cut_chevron(tmp->cmd);
		tmp->cmd = ft_chwc(tmp->cmd);
		if (g_data->is_pipe == 1 && tmp->next && what_im(tmp->next->cmd) == 3)
			ret = pipex(tmp->cmd);
		else if (g_data->is_pipe == 1 && what_im(tmp->cmd) == 0)
		{
			g_data->is_pipe = 0;
			dup2(tmp->redirect.infd, 0);
			dup2(tmp->redirect.outfd, 1);
			ret = exec(tmp->cmd);
		}
		tmp = tmp->next;
	}
	return (ret);
}

void	redirect_exec(t_token *token, int mode)
{
	g_data->stdin_reset = dup(0);
	g_data->stdout_reset = dup(1);
	dup2(token->redirect.infd, 0);
	dup2(token->redirect.outfd, 1);
	if (mode == 0)
		g_data->lastret = exec(token->cmd);
	else
	{
		g_data->is_pipe = 1;
		g_data->lastret = exec_pipe(token);
	}
	dup2(g_data->stdin_reset, 0);
	dup2(g_data->stdout_reset, 1);
}

void	execute(t_token *token)
{
	int		start;
	t_token	*tmp;
	int		is_and;
	int		is_or;
	int		is_ope;

	start = 1;
	tmp = token;
	is_and = 0;
	is_or = 0;
	is_ope = 1;
	g_data->is_pipe = 0;
	while (tmp)
	{
		tmp->cmd = ft_add_q_dollar(tmp->cmd);
		tmp->cmd = ft_chdollar(tmp->cmd);
		ft_redirect_for_john(tmp);
		tmp->cmd = ft_cut_chevron(tmp->cmd);
		tmp->cmd = ft_chwc(tmp->cmd);
		if (what_im(tmp->cmd) == 0)
		{
			if (is_and == 1 && g_data->lastret == 0)
			{
				is_and = 0;
				if (g_data->is_pipe == 0 && tmp->next
					&& what_im(tmp->next->cmd) == 3 && tmp->redirect.outfd == 1)
					redirect_exec(tmp, 1);
				else
					redirect_exec(tmp, 0);
			}
			else if (is_or == 1 && g_data->lastret != 0)
			{
				is_or = 0;
				if (g_data->is_pipe == 0 && tmp->next
					&& what_im(tmp->next->cmd) == 3 && tmp->redirect.outfd == 1)
					redirect_exec(tmp, 1);
				else
					redirect_exec(tmp, 0);
			}
			else if (start == 1 && g_data->is_pipe == 0 && tmp->next
				&& what_im(tmp->next->cmd) == 3 && tmp->redirect.outfd == 1)
				redirect_exec(tmp, 1);
			else if (start == 1)
				redirect_exec(tmp, 0);
		}
		else
		{
			if (start == 0 && what_im(tmp->cmd) == 1)
				is_and = 1;
			else if (start == 0 && what_im(tmp->cmd) == 2)
				is_or = 1;
		}
		tmp = tmp->next;
		start = 0;
	}
}
