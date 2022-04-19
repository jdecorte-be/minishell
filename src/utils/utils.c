/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:00:52 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 21:01:02 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_free(char *line)
{
	free(line);
	return (1);
}

int	ft_str_isspace(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	ft_exist(char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (str[i] && i < len)
		i++;
	if (i == len)
		return (1);
	return (0);
}

char	*ft_lstmerge(t_list *lst)
{
	char	*str;
	t_list	*tmp;

	if (!lst)
		return (0);
	str = 0;
	while (lst)
	{
		if (lst->next)
			str = ft_trijoin1(str, lst->content, " ");
		else
			str = ft_strjoin1(str, lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
	return (str);
}

char	*ft_woquote(char *line)
{
	char	*str;
	size_t	i;
	char	c;
	size_t	i2;

	if (!line)
		return (0);
	if (ft_strchr(line, '\'') || ft_strchr(line, '\"'))
	{
		str = ft_calloc(sizeof(char), (ft_strlen(line) - 2 + 1));
		i = 0;
		i2 = 0;
		while (line[i2])
		{
			if (line[i2] && ft_strchr("\'\"", line[i2]))
			{
				c = line[i2++];
				while (line[i2] && line[i2] != c)
					str[i++] = line[i2++];
				i2++;
			}
			else if (line[i2])
				str[i++] = line[i2++];
		}
		str[i] = 0;
	}
	else
		return (ft_strdup(line));
	return (str);
}
