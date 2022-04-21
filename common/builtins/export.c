/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:14:20 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/03 21:29:26 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkvalid(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((ft_isalnum(cmd[i]) == 0 && cmd[i] != '\''
				&& cmd[i] != '"' && cmd[i] != '_' && cmd)
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

void	export_print_2(char **env, int i, int j)
{
	char	*temp;

	if (ft_strcmp(env[i], env[j]) > 0 && env[i] && env[j])
	{
		temp = env[i];
		env[i] = env[j];
		env[j] = temp;
	}
}

void	export_print(void)
{
	int		len;
	char	**env;
	int		i;
	int		j;

	i = 0;
	len = splitlen(g_data->env);
	env = array_dup();
	if (env == NULL)
		return ;
	while (i < len)
	{
		j = i + 1;
		while (++j < len)
			export_print_2(env, i, j);
		if (env[i])
			format_env(env[i]);
		i++;
	}
}

int	export(char **cmd)
{
	int		i;
	char	*tmp;

	i = 1;
	if (!cmd[1])
	{
		export_print();
		return (0);
	}
	while (cmd[i])
	{
		if (cmd[i][0] == '_' && cmd[i][1] == '=')
			return (0);
		if (!checkvalid(ft_ecrase_q(cmd[i])))
			return (1);
		tmp = ft_ecrase_q(cmd[i]);
		my_setenv(tmp);
		free(tmp);
		i++;
	}
	return (0);
}
