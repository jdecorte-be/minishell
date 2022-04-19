/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chwc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:47:02 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/25 15:39:54 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_chwc_ok(char *line);
void	ft_chwc_str2(t_tmp *tmp, t_list **name, t_list **wc, t_list **woq);
void	ft_chwc_str3(t_tmp *tmp, char *line, t_list **wc, int e);
char	*ft_chwc_str(char *line, t_list *name, t_list *wc, t_list *woq);
t_list	*ft_chwc2_1(t_tmp *tmp);

void	ft_chwc2_2(t_tmp *tmp, char *line)
{
	tmp->i = 0;
	tmp->tab = ft_split4(line, "/");
	while (tmp->tab[tmp->i] && !ft_strchr(tmp->tab[tmp->i], '*'))
		tmp->i++;
	if (tmp->tab[tmp->i])
		tmp->str = ft_strdup(tmp->tab[tmp->i]);
	tmp->i2 = 0;
	tmp->tmp = 0;
	while (tmp->i2 < tmp->i)
		tmp->tmp = ft_strjoin1(tmp->tmp, tmp->tab[tmp->i2++]);
}

void	ft_chwc2_free(char *pref, char *suff, t_tmp *tmp)
{
	free(pref);
	free(suff);
	free(tmp->tab);
}

char	*ft_chwc2(char *line)
{
	t_tmp	tmp;
	char	*pref;
	char	*suff;
	t_list	*match;
	t_list	*match2;

	ft_chwc2_2(&tmp, line);
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
		tmp.lst->content = ft_trijoin(pref, tmp.lst->content, suff, 0);
		tmp.lst = tmp.lst->next;
	}
	tmp.lst = match;
	match2 = ft_chwc2_1(&tmp);
	ft_lstclear(&match, free);
	ft_chwc2_free(pref, suff, &tmp);
	return (ft_lstmerge(match2));
}

void	ft_chwc_2(t_tmp *tmp, t_list **woq, t_list **wc, t_list **name)
{
	while (tmp->lst)
	{
		ft_lstadd_back(name, ft_lstnew(ft_chwc2((tmp->lst)->content)));
		tmp->lst = (tmp->lst)->next;
	}
	tmp->lst = *wc;
	while (tmp->lst)
	{
		ft_lstadd_back(woq, ft_lstnew(ft_woquote((tmp->lst)->content)));
		tmp->lst = (tmp->lst)->next;
	}
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
	ft_chwc_2(&tmp, &woq, &wc, &name);
	if (!name)
		return (line);
	str = ft_chwc_str(line, name, wc, woq);
	free(line);
	return (str);
}
