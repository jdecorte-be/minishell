/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:22:28 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 16:23:56 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo(char **cmd)
{
	int	i;
	int	j;
	int	option;

	i = 1;
	j = 1;
	option = 0;
	if (!cmd[1])
	{
		ft_putstr_fd("\n", 1);
		ft_free_tab(cmd);
		return (0);
	}
	while (cmd[i] && cmd[i][0] == '-')
	{
		j = 1;
		while (cmd[i][j] && cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
		{
			i++;
			option = 1;
		}
		else
			break ;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
	ft_free_tab(cmd);
	return (0);
}
