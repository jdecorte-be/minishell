/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:55:03 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/22 17:56:35 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_chdollar_ok(char *line);
size_t	ft_chdollar_len(char *line, t_list **dollar);

void	ft_chdollar_str_2_1(t_tmp *tmp, char *line, t_list **dollar)
{
	if (line[tmp->i] && line[tmp->i] != '\"' && (line[tmp->i] == '?'
			|| ft_isdigit(line[tmp->i])) && ++tmp->i)
	{
		tmp->i2 = ft_strlcat(tmp->str,
				(*dollar)->content, tmp->len);
		(*dollar) = ft_next((*dollar));
	}
	else if (line[tmp->i] != '\"')
	{
		while (line[tmp->i] && line[tmp->i] != '\"'
			&& (ft_isalnum(line[tmp->i])
				|| ft_strchr("?", line[tmp->i])))
			tmp->i++;
		tmp->i2 = ft_strlcat(tmp->str,
				(*dollar)->content, tmp->len);
		(*dollar) = ft_next((*dollar));
	}
}

void	ft_chdollar_str_2(t_tmp *tmp, char *line, t_list **dollar)
{
	if (line[tmp->i] == '\'')
	{
		tmp->str[tmp->i2++] = line[tmp->i++];
		while (line[tmp->i] && line[tmp->i] != '\'')
			tmp->str[tmp->i2++] = line[tmp->i++];
		tmp->str[tmp->i2++] = line[tmp->i++];
	}
	else if (line[tmp->i] == '\"')
	{
		tmp->str[tmp->i2++] = line[tmp->i++];
		while (line[tmp->i] && line[tmp->i] != '\"')
		{
			while (line[tmp->i] && line[tmp->i] != '\"' && line[tmp->i] != '$')
				tmp->str[tmp->i2++] = line[tmp->i++];
			if (line[tmp->i] && line[tmp->i] != '\"' && line[tmp->i + 1]
				&& line[tmp->i] == '$' && (ft_isalnum(line[tmp->i + 1])
					|| ft_strchr("_?", line[tmp->i + 1])) && ++tmp->i)
				ft_chdollar_str_2_1(tmp, line, dollar);
			else if (line[tmp->i] && line[tmp->i] != '\"')
				tmp->str[tmp->i2++] = line[tmp->i++];
		}
		if (line[tmp->i])
			tmp->str[tmp->i2++] = line[tmp->i++];
	}
}

void	ft_chdollar_str_3(t_tmp *tmp, char *line, t_list **dollar)
{
	if ((line[tmp->i] == '?' || ft_isdigit(line[tmp->i])) && ++tmp->i)
	{
		tmp->i2 = ft_strlcat(tmp->str, (*dollar)->content, tmp->len);
		(*dollar) = ft_next((*dollar));
	}
	else
	{
		while (line[tmp->i] && (ft_isalnum(line[tmp->i])
				|| ft_strchr("?", line[tmp->i])))
			tmp->i++;
		tmp->i2 = ft_strlcat(tmp->str, (*dollar)->content, tmp->len);
		(*dollar) = ft_next((*dollar));
	}
}

char	*ft_chdollar_str(char *str, char *line, t_list *dollar, size_t len)
{
	t_tmp	tmp;

	tmp.len = len;
	tmp.str = str;
	tmp.i = 0;
	tmp.i2 = 0;
	while (line[tmp.i])
	{
		if (ft_strchr("\'\"", line[tmp.i]))
			ft_chdollar_str_2(&tmp, line, &dollar);
		else if (line[tmp.i] && line[tmp.i + 1] && line[tmp.i] == '$'
			&& (ft_isalnum(line[tmp.i + 1])
				|| ft_strchr("?", line[tmp.i + 1])) && ++tmp.i)
			ft_chdollar_str_3(&tmp, line, &dollar);
		else if (line[tmp.i] && line[tmp.i] == '$' && line[tmp.i + 1]
			&& ft_strchr("\'\"", line[tmp.i + 1]))
			tmp.i++;
		else if (line[tmp.i])
		{
			tmp.str[tmp.i2++] = line[tmp.i++];
		}
	}
	tmp.str[tmp.i2] = 0;
	return (tmp.str);
}

char	*ft_chdollar(char *line)
{
	size_t	len;
	char	*str;
	t_list	*dollar;

	if (!line)
		return (0);
	if (ft_chdollar_ok(line))
		return (line);
	dollar = 0;
	len = ft_chdollar_len(line, &dollar);
	str = ft_calloc(sizeof(*str), len + 1);
	str = ft_chdollar_str(str, line, dollar, len);
	free(line);
	return (str);
}
