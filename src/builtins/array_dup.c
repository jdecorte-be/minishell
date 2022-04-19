/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:04:50 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/07 17:05:36 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
