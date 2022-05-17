/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte-be <jdecorte@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:02:12 by jdecorte-be           #+#    #+#             */
/*   Updated: 2022/05/10 16:41:48 by jdecorte-be           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_next_word(char *line, size_t i)
{
	char	c;

	while (line[i] && !ft_isspace(line[i]))
	{
		if (ft_strchr("\"\'", line[i]))
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				i++;
			if (line[i])
				i++;
		}
		else
			i++;
	}
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

int	ft_next_cmd(char *line, size_t i)
{
	while (line[i] && !ft_strchr("|&", line[i]))
		i++;
	while (line[i] && (ft_strchr("|&", line[i]) || ft_isspace(line[i])))
		i++;
	return (i);
}

int	ft_after_p(char *line, size_t i)
{
	ft_skip_p(line, &i);
	return (i);
}
