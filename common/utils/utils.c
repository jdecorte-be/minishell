/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:00:52 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/09 22:44:57 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			str = ft_trijoin(str, lst->content, " ", 1);
		else
			str = ft_strjoin1(str, lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
	return (str);
}

void	ft_woquote_2(char *line, int *i, int *i2, char *str)
{
	char	c;

	if (line[*i2] && ft_strchr("\'\"", line[*i2]))
	{
		c = line[*i2++];
		while (line[*i2] && line[*i2] != c)
			str[*i++] = line[*i2++];
		i2++;
	}
	else if (line[*i2])
		str[*i++] = line[*i2++];
}

void	ft_woquote_3(char *line, char *str)
{
	int		i;
	int		i2;

	str = ft_calloc(sizeof(char), (ft_strlen(line) - 2 + 1));
	i = 0;
	i2 = 0;
	while (line[i2])
		ft_woquote_2(line, &i, &i2, str);
	str[i] = 0;
}

char	*ft_woquote(char *line)
{
	char	*str;

	str = NULL;
	if (!line)
		return (0);
	if (ft_strchr(line, '\'') || ft_strchr(line, '\"'))
		ft_woquote_3(line, str);
	else
		return (ft_strdup(line));
	return (str);
}
