/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epur_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:50:36 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 20:50:37 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 12))
		return (1);
	return (0);
}

static void	ft_epur_len2(char *line, size_t *i, size_t *count)
{
	char	c;

	c = line[(*i)++];
	while (line[*i] && line[(*i)++] != c)
		(*count)++;
	(*count)++;
}

static size_t	ft_epur_len(char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i] && ft_strchr("\'\"", line[i]) && ++count)
			ft_epur_len2(line, &i, &count);
		while (line[i] && !ft_isspace(line[i]) && !ft_strchr("\'\"", line[i])
			&& ++i)
			count++;
		if (line[i] && ft_isspace(line[i]))
			count++;
	}
	if (!line[i] && i > 0 && line[i - 1] && ft_isspace(line[i - 1]))
		count--;
	return (count);
}

char	*ft_epur_str2(char *str, char *line, size_t *i2, size_t *i)
{
	char	c;

	while (line[*i])
	{
		while (line[*i] && ft_isspace(line[*i]))
			(*i)++;
		if (line[*i] && ft_strchr("\'\"", line[*i]))
		{
			str[(*i2)++] = line[*i];
			c = line[(*i)++];
			while (line[*i] && line[*i] != c)
				str[(*i2)++] = line[(*i)++];
			if (line[(*i)])
				str[(*i2)++] = line[(*i)++];
		}
		while (line[*i] && !ft_isspace(line[*i]) && !ft_strchr("\'\"", line[*i]))
			str[(*i2)++] = line[(*i)++];
		if (line[*i] && ft_isspace(line[*i]))
			str[(*i2)++] = ' ';
	}
	return (str);
}

char	*ft_epur_str(char *line)
{
	char	*str;
	size_t	i;
	size_t	i2;

	if (!line)
		return (0);
	str = malloc(sizeof(char) * (ft_epur_len(line) + 1));
	if (!str)
		ft_error(2);
	i = 0;
	i2 = 0;
	str = ft_epur_str2(str, line, &i2, &i);
	if (i > 0 && i2 > 0 && ft_isspace(line[i - 1]))
		i2--;
	str[i2] = 0;
	free(line);
	return (str);
}
