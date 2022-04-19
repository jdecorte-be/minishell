/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chwc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:47:02 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 20:49:09 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*ft_chwc_str(char *line, t_list *name, t_list *wc, t_list *woq)
{
	size_t	start;
	size_t	end;
	char	*str;
	size_t	len;
	size_t	i;

	end = 0;
	str = 0;
	while (line[end])
	{
		start = end;
		if (wc)
		{
			len = ft_strlen(wc->content);
			if (line[end] && ft_exist(line + end, len - 1)
				&& !ft_strncmp(line + end, wc->content, len -1))
			{
				i = 0;
				while (((char *)(wc->content))[i] && ++i)
					end++;
				if (name->content)
					str = ft_strjoin1(str, name->content);
				else
					str = ft_strjoin1(str, woq->content);
				woq = ft_next(woq);
				wc = ft_next(wc);
				name = ft_next(name);
			}
			else
			{
				while (line[end] && ft_exist(line + end, len - 1)
					&& ft_strncmp(line + end, wc->content, len -1))
					end++;
				str = ft_strjoin3(str, ft_substr(line, start, end - start));
			}
		}
		else
		{
			while (line[end])
				end++;
			str = ft_strjoin3(str, ft_substr(line, start, end - start));
		}
	}
	return (str);
}

char	*ft_chwc2(char *line)
{
	t_tmp	tmp;
	char	*pref;
	char	*suff;
	t_list	*match;
	t_list	*match2;
	void	*home;

	tmp.i = 0;
	tmp.tab = ft_split4(line, "/");
	while (tmp.tab[tmp.i] && !ft_strchr(tmp.tab[tmp.i], '*'))
		tmp.i++;
	if (tmp.tab[tmp.i])
		tmp.str = ft_strdup(tmp.tab[tmp.i]);
	tmp.i2 = 0;
	tmp.tmp = 0;
	while (tmp.i2 < tmp.i)
		tmp.tmp = ft_strjoin1(tmp.tmp, tmp.tab[tmp.i2++]);
	pref = tmp.tmp;
	tmp.i2 = tmp.i + 1;
	suff = 0;
	while (tmp.tab[tmp.i2])
		suff = ft_strjoin1(suff, tmp.tab[tmp.i2++]);
	match = ft_wcfile(tmp.str, getcwd(tmp.path, PATH_MAX), 0, 0);
	free(tmp.str);
	tmp.lst = match;
	while (tmp.lst)
	{
		tmp.lst->content = ft_trijoin2(pref, tmp.lst->content, suff);
		tmp.lst = tmp.lst->next;
	}
	tmp.lst = match;
	match2 = 0;
	home = getcwd(tmp.path, PATH_MAX);
	while (tmp.lst)
	{
		if (!access(tmp.lst->content, F_OK))
			ft_lstadd_back(&match2, ft_lstnew(ft_strdup(tmp.lst->content)));
		else if (!access(ft_trijoin(home,
					"/", ft_strdup(tmp.lst->content)), F_OK))
			ft_lstadd_back(&match2, ft_lstnew(ft_strdup(tmp.lst->content)));
		tmp.lst = tmp.lst->next;
	}
	free(pref);
	free(suff);
	ft_lstclear(&match, free);
	ft_free_tab(tmp.tab);
	return (ft_lstmerge(match2));
}

char	*ft_chwc(char *line)
{
	char	*str;
	t_list	*woq;
	t_list	*name;
	t_list	*wc;
	t_tmp	tmp;

	woq = 0;
	wc = 0;
	name = 0;
	if (!line)
		return (0);
	if (ft_chwc_ok(line))
		return (line);
	wc = ft_wcsearch(line);
	tmp.lst = wc;
	while (tmp.lst)
	{
		ft_lstadd_back(&name, ft_lstnew(ft_chwc2((tmp.lst)->content)));
		tmp.lst = (tmp.lst)->next;
	}
	tmp.lst = wc;
	while (tmp.lst)
	{
		ft_lstadd_back(&woq, ft_lstnew(ft_woquote((tmp.lst)->content)));
		tmp.lst = (tmp.lst)->next;
	}
	if (!name)
		return (line);
	str = ft_chwc_str(line, name, wc, woq);
	free(line);
	return (str);
}
