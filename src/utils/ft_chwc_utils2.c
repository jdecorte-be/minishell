/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chwc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:46:51 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 20:46:56 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_wc_in_fw(char *line)
{
	size_t	i;
	char	c;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i] && !ft_isspace(line[i]))
	{
		if (ft_strchr("\"\'", line[i]))
		{
			c = line[i++];
			while (line[i] && !ft_isspace(line[i]) && line[i] != c)
				i++;
			if (line[i] && !ft_isspace(line[i]))
				i++;
		}
		else if (line[i] == '*')
			return (0);
		else
			i++;
	}
	return (1);
}
