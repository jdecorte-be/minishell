/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:01:57 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 21:02:07 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strstrchr(char *str, char *set)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(set, str[i]))
			return (str[i]);
	}
	return (0);
}

void	ft_skip_q(char *str, size_t *i)
{
	char	c;

	c = str[(*i)++];
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (str[*i])
		(*i)++;
}

void	ft_skip_p(char *str, size_t *i)
{
	int	par;

	par = 1;
	(*i)++;
	while (str[*i] && par)
	{
		if (str[*i] == '(')
			par++;
		else if (str[*i] == ')')
			par--;
		(*i)++;
	}
}
