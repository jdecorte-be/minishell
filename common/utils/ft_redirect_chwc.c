/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_chwc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:50:47 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/25 15:39:54 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_wcsearch2_1(t_tmp *tmp, char *line);
t_list	*ft_wcsearch2(char *line);

int	ft_chwc_ok2(char *line)
{
	size_t	i;
	char	c;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (ft_strchr("\"\'", line[i]))
			ft_skip_q(line, &i);
		else if (line[i] == '(')
			ft_skip_p(line, &i);
		else if (line[i] == '*')
			return (0);
		else
			i++;
	}
	return (1);
}

void	ft_transf2(t_tmp *tmp, char **suff, char **pref)
{
	while (tmp->tab[tmp->i] && !ft_strchr(tmp->tab[tmp->i], '*'))
		tmp->i++;
	if (tmp->tab[tmp->i])
		tmp->str = tmp->tab[tmp->i];
	tmp->i2 = 0;
	tmp->tmp = 0;
	while (tmp->i2 < tmp->i)
		tmp->tmp = ft_strjoin1(tmp->tmp, tmp->tab[tmp->i2++]);
	*pref = tmp->tmp;
	tmp->i2 = tmp->i + 1;
	*suff = 0;
	while (tmp->tab[tmp->i2])
		*suff = ft_strjoin1(*suff, tmp->tab[tmp->i2++]);
}

char	*ft_transf(char *line)
{
	t_tmp	tmp;
	char	*pref;
	char	*suff;
	t_list	*match;
	t_list	*match2;

	tmp.i = 0;
	tmp.tab = ft_split4(line, "/");
	ft_transf2(&tmp, &suff, &pref);
	match = ft_wcfile(tmp.str, getcwd(tmp.path, PATH_MAX), 0, 0);
	if (ft_lstsize(match) > 1)
	{
		ft_lstclear(&match, free);
		printf("pas bien trop grand\n");
		return (0);
	}
	tmp.lst = match;
	tmp.lst->content = ft_trijoin(pref, tmp.lst->content, suff, 2);
	match2 = 0;
	if (!access(tmp.lst->content, F_OK))
		ft_lstadd_back(&match2, ft_lstnew(tmp.lst->content));
	else if (!access(ft_trijoin(tmp.path, "/", tmp.lst->content, 2), F_OK))
		ft_lstadd_back(&match2, ft_lstnew(tmp.lst->content));
	return (ft_lstmerge(match2));
}

void	ft_redirect_chwc2(t_list **tmp, t_list **name, t_list **woq, int e)
{
	if (e == 1)
	{
		while (*tmp)
		{
			ft_lstadd_back(name, ft_lstnew(
					ft_transf(ft_ecrase_q((*tmp)->content))));
			*tmp = (*tmp)->next;
		}
	}
	if (e == 2)
	{
		while (*tmp)
		{
			ft_lstadd_back(woq, ft_lstnew(ft_woquote((*tmp)->content)));
			*tmp = (*tmp)->next;
		}
	}
}

char	*ft_redirect_chwc(char *line)
{
	char	*str;
	t_list	*wc;
	t_list	*name;
	t_list	*tmp;
	t_list	*woq;

	if (!line)
		return (0);
	if (ft_chwc_ok2(line))
		return (line);
	wc = ft_wcsearch2(line);
	name = 0;
	tmp = wc;
	woq = 0;
	ft_redirect_chwc2(&tmp, &name, &woq, 1);
	tmp = wc;
	ft_redirect_chwc2(&tmp, &name, &woq, 2);
	if (!name)
		return (line);
	str = ft_chwc_str(line, name, wc, woq);
	free(line);
	return (str);
}
