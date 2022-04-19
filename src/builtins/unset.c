/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:53:46 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 17:55:30 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	del_element(char *name)
{
	char	**p_env;
	char	**p_env2;

	p_env = g_data->env;
	while (*p_env)
	{
		if (ft_strncmp(*p_env, name, ft_strlen(name) - 1) == 0)
		{
			p_env2 = p_env;
			while (*p_env2)
			{
				*p_env2 = *(p_env2 + 1);
				p_env2++;
			}
		}
		p_env++;
	}
	return (0);
}

int	unset(char **cmd)
{
	int	offset;
	int	i;

	i = 1;
	if (!cmd[1])
	{
		ft_free_tab(cmd);
		return (0);
	}
	while (cmd[i])
	{
		if (!checkvalid(cmd[i]))
		{
			ft_free_tab(cmd);
			return (1);
		}
		del_element(ft_ecrase_q(cmd[i]));
		i++;
	}
	ft_free_tab(cmd);
	return (0);
}
