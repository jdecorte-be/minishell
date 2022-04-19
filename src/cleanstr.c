/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:15:51 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/07 15:25:40 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	tokenize_2(char *line, int i)
{
	if (line[i] && line[i] == '|')
	{
		if (i)
			line[i - 1] = 1;
		if (line[i + 1])
			line[i + 1] = 1;
		i++;
	}
	else
		i++;
	return (i);
}

char	*tokenize(char *line)
{
	size_t	i;

	if (!line)
		return (line);
	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '(')
			ft_skip_p(line, &i);
		else if (line[i] && ft_strchr("\'\"", line[i]))
			ft_skip_q(line, &i);
		else if (line[i] && line[i + 1] && (ft_strnstr(line + i, "&&", 2)
				|| ft_strnstr(line + i, "||", 2)))
		{
			if (i)
				line[i - 1] = 1;
			if (line[i + 2])
				line[i + 2] = 1;
			i += 2;
		}
		else
			i = tokenize_2(line, i);
	}
	return (line);
}
