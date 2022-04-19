/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chwc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:04:24 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/04/25 15:39:54 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_chwc_ok(char *line)
{
	size_t	i;
	char	c;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("\"\'", line[i]))
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				i++;
			if (line[i])
				i++;
		}
		else if (line[i] == '*')
			return (0);
		else
			i++;
	}
	return (1);
}

void	ft_chwc_str2(t_tmp *tmp, t_list **name, t_list **wc, t_list **woq)
{
	size_t	i;

	i = 0;
	while (((char *)((*wc)->content))[i++])
		tmp->end++;
	if ((*name)->content)
		tmp->str = ft_strjoin1(tmp->str, (*name)->content);
	else
		tmp->str = ft_strjoin1(tmp->str, (*woq)->content);
	*woq = ft_next(*woq);
	*wc = ft_next(*wc);
	*name = ft_next(*name);
}

void	ft_chwc_str3(t_tmp *tmp, char *line, t_list **wc, int e)
{
	if (e == 1)
	{
		while (line[tmp->end] && ft_exist(line + tmp->end, tmp->len - 1)
			&& ft_strncmp(line + tmp->end, (*wc)->content, tmp->len -1))
			tmp->end++;
		tmp->str = ft_strjoin3(tmp->str,
				ft_substr(line, tmp->start, tmp->end - tmp->start));
	}
	else if (e == 2)
	{
		while (line[tmp->end])
			tmp->end++;
		tmp->str = ft_strjoin3(tmp->str,
				ft_substr(line, tmp->start, tmp->end - tmp->start));
	}
}

char	*ft_chwc_str(char *line, t_list *name, t_list *wc, t_list *woq)
{
	t_tmp	tmp;

	tmp.end = 0;
	tmp.str = 0;
	while (line[tmp.end])
	{
		tmp.start = tmp.end;
		if (wc)
		{
			tmp.len = ft_strlen(wc->content);
			if (line[tmp.end] && ft_exist(line + tmp.end, tmp.len - 1)
				&& !ft_strncmp(line + tmp.end, wc->content, tmp.len -1))
				ft_chwc_str2(&tmp, &name, &wc, &woq);
			else
				ft_chwc_str3(&tmp, line, &wc, 1);
		}
		else
			ft_chwc_str3(&tmp, line, &wc, 2);
	}
	return (tmp.str);
}

t_list	*ft_chwc2_1(t_tmp *tmp)
{
	t_list	*match2;

	match2 = 0;
	tmp->home2 = getcwd(tmp->path, PATH_MAX);
	while (tmp->lst)
	{
		if (!access(tmp->lst->content, F_OK))
			ft_lstadd_back(&match2, ft_lstnew(ft_strdup(tmp->lst->content)));
		else if (!access(ft_trijoin(tmp->home2,
					"/", ft_strdup(tmp->lst->content), 3), F_OK))
			ft_lstadd_back(&match2, ft_lstnew(ft_strdup(tmp->lst->content)));
		tmp->lst = tmp->lst->next;
	}
	return (match2);
}
