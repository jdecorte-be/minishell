/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:14:20 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 18:20:09 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	checkvalid(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((ft_isalnum(cmd[i]) == 0 && cmd[i] != '\''
				&& cmd[i] != '"' && cmd[i] != '_')
			|| ft_isdigit(cmd[0]) == 1 || cmd[0] == '=')
		{
			puterror(cmd, "not a valid identifier");
			return (0);
		}
		i++;
		if (cmd[i] == '=')
			break ;
	}
	return (1);
}

char	**array_dup(char **tab)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * splitlen(g_data->env));
	if (!res)
		return (NULL);
	while (i < splitlen(g_data->env))
	{
		res[i] = ft_strdup(g_data->env[i]);
		if (!res[i])
			return (NULL);
		i++;
	}
	return (res);
}

void	export_print(void)
{
	int		len;
	char	**env;
	int		i;
	int		j;
	char	*temp;

	i = 0;
	len = splitlen(g_data->env);
	env = array_dup(g_data->env);
	if (env == NULL)
		return ;
	while (i < len)
	{
		j = i + 1;
		while (++j < len)
		{
			if (ft_strcmp(env[i], env[j]) > 0 && env[i] && env[j])
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			if (env[i])
				format_env(env[i]);
		}
		i++;
	}
	i = -1;
	while (++i < len)
		free(env[i]);
	free(env);
}

int	export(char **cmd)
{
	int	i;

	if (!cmd[1])
	{
		export_print();
		ft_free_tab(cmd);
		return (0);
	}
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i][0] == '_' && cmd[i][1] == '=')
		{
			ft_free_tab(cmd);
			return (0);
		}
		if (!checkvalid(ft_ecrase_q(cmd[i])))
		{
			ft_free_tab(cmd);
			return (0);
		}
		my_setenv(ft_ecrase_q(cmd[i]), 1);
	}
	g_data->lastret = 0;
	ft_free_tab(cmd);
	return (0);
}
