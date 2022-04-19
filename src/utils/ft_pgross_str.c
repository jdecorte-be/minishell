/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pgross_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:50:42 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/21 16:28:23 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	ft_pgross_len(char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_strchr("\'\"", line[i]))
			ft_skip_q(line, &i);
		else if ((!ft_strncmp(&line[i], "&&", 1)
				|| !ft_strncmp(&line[i], "||", 1)
				|| !ft_strncmp(&line[i], ">>", 1)
				|| !ft_strncmp(&line[i], "<<", 1)) && ++i && ++i)
			count += 2;
		else if (ft_strchr("()&|<>", line[i]) && ++i)
			count += 2;
		else
			i++;
	}
	return (i + count);
}

void	ft_pgross_creat3(char *str, size_t *i, size_t *i2, char *line)
{
	str[(*i)++] = ' ';
	str[(*i)++] = line[(*i2)++];
	str[(*i)++] = line[(*i2)++];
	str[(*i)++] = ' ';
}

void	ft_pgross_creat2(char *str, size_t *i, size_t *i2, char *line)
{
	char	c;

	if (ft_strchr("\'\"", line[*i2]))
	{
		c = line[*i2];
		str[(*i)++] = line[(*i2)++];
		while (line[*i2] && line[*i2] != c)
			str[(*i)++] = line[(*i2)++];
		str[(*i)++] = line[(*i2)++];
	}
	else if (!ft_strncmp(&line[*i2], "&&", 1)
		|| !ft_strncmp(&line[*i2], "||", 1)
		|| !ft_strncmp(&line[*i2], ">>", 1)
		|| !ft_strncmp(&line[*i2], "<<", 1))
		ft_pgross_creat3(str, i, i2, line);
	else if (ft_strchr("()|&<>", line[*i2]))
	{
		str[(*i)++] = ' ';
		str[(*i)++] = line[(*i2)++];
		str[(*i)++] = ' ';
	}
	else
		str[(*i)++] = line[(*i2)++];
}

static char	*ft_pgross_creat(char *str, char *line)
{
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	while (line[i2])
		ft_pgross_creat2(str, &i, &i2, line);
	str[i] = 0;
	return (str);
}

char	*ft_pgross_str(char *line)
{
	char	*newline;
	size_t	len;

	if (!line)
		return (0);
	len = ft_pgross_len(line);
	newline = malloc(sizeof(char) * (len + 1));
	newline = ft_pgross_creat(newline, line);
	free(line);
	return (newline);
}
