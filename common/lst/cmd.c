/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:12:48 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/03 16:08:49 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_cmdnew(char *newline, t_cmd *sup_cmd, t_redirect redirect)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		ft_error(2);
	cmd->line = newline;
	cmd->redirect = redirect;
	cmd->sup_cmd = sup_cmd;
	cmd->sub_cmd = 0;
	cmd->back = 0;
	cmd->and = 0;
	cmd->or = 0;
	return (cmd);
}

t_cmd	*ft_cmdfist(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return (cmd);
	tmp = cmd;
	while (tmp->back)
		tmp = tmp->back;
	return (tmp);
}

void	ft_cmdadd_and(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last_elem;

	last_elem = NULL;
	if (cmd && new)
	{
		if (!*cmd)
			*cmd = new;
		else
			last_elem->and = new;
	}
}

void	ft_cmdadd_or(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last_elem;

	last_elem = NULL;
	if (cmd && new)
	{
		if (!*cmd)
			*cmd = new;
		else
			last_elem->or = new;
	}
}
