/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdollar3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:58:36 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/04/25 15:39:54 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_chdollar_ok(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '\"' && ++i)
		{
			while (line[i] && line[i] != '\"')
			{
				if (line[i] && line[i] == '$')
					return (0);
				i++;
			}
			if (line[i])
				i++;
		}
		else if (line[i] && line[i] == '\'')
			ft_skip_q(line, &i);
		else if (line[i] && line[i] == '$')
			return (0);
		else if (line[i])
			i++;
	}
	return (1);
}
