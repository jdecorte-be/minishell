/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:00:44 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/07 20:24:38 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_count_words2(char *str, size_t *i, char *set)
{
	char	c;

	if (str[*i] && ft_strchr("\'\"", str[*i]))
	{
		c = str[(*i)++];
		while (str[*i] && c != str[*i])
			(*i)++;
		if (str[*i])
			(*i)++;
	}
	if (str[*i] && !ft_strchr(set, str[*i]) && !ft_strchr("\'\"", str[*i]))
		while (str[*i] && !ft_strchr(set, str[*i]) && !ft_strchr("\'\"", str[*i]))
			(*i)++;
}

void	ft_creat_tab2_2(char *str, size_t *end, char *set)
{
	if (str[*end] && ft_strchr("\'\"", str[*end]))
		ft_creat_tab2(str, end, set, 1);
	if (str[*end] && !ft_strchr(set, str[*end])
		&& !ft_strchr("\'\"", str[*end]))
		while (str[*end] && !ft_strchr(set, str[*end])
			&& !ft_strchr("\'\"", str[*end]))
			(*end)++;
}

void	ft_creat_tab2(char *str, size_t *end, char *set, int e)
{
	char	c;

	if (e == 1)
	{
		c = str[(*end)++];
		while (str[*end] && c != str[*end])
			(*end)++;
		if (str[*end])
			(*end)++;
	}
	if (e == 2)
	{
		while (ft_isspace(str[*end]))
			(*end)--;
		(*end)++;
	}
	if (e == 3)
		ft_creat_tab2_2(str, end, set);
}
