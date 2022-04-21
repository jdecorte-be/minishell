/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:53:46 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/04 23:47:31 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkvalid_unset(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[0] == '-')
			return (2);
		if ((ft_isalnum(cmd[i]) == 0 && cmd[i] != '\''
				&& cmd[i] != '"' && cmd[i] != '_' && cmd)
			|| ft_isdigit(cmd[0]) == 1)
		{
			puterror(cmd, "not a valid identifier");
			return (1);
		}
		i++;
		if (cmd[i] == '=')
			break ;
	}
	return (0);
}

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
	free(name);
	return (0);
}

int	unset(char **cmd)
{
	int	i;
	int	err;

	i = 1;
	if (!cmd[1])
		return (0);
	while (cmd[i])
	{
		err = checkvalid_unset(cmd[i]);
		if (err != 0)
			return (err);
		del_element(ft_ecrase_q(cmd[i]));
		i++;
	}
	return (0);
}
