/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_chwc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:26:38 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/08 19:41:53 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_wcsearch2_1(t_tmp *tmp, char *line)
{
	if (ft_strchr("\'\"", line[tmp->end]))
		ft_skip_q(line, &tmp->end);
	else if (line[tmp->end] == '*' && ++tmp->end)
		tmp->c = 1;
	else
		tmp->end++;
}

t_list	*ft_wcsearch2(char *line)
{
	t_tmp	tmp;
	t_list	*wc;

	tmp.end = 0;
	wc = 0;
	while (line[tmp.end])
	{
		tmp.c = 0;
		if (line[tmp.end] && line[tmp.end] == '(')
			ft_skip_p(line, &tmp.end);
		else if (line[tmp.end] && !ft_isspace(line[tmp.end])
			&& line[tmp.end] != '(')
		{
			tmp.start = tmp.end;
			while (line[tmp.end] && !ft_isspace(line[tmp.end])
				&& line[tmp.end] != '(')
				ft_wcsearch2_1(&tmp, line);
			if (tmp.c == 1)
				ft_lstadd_back(&wc, ft_lstnew(ft_substr(line,
							tmp.start, tmp.end - tmp.start)));
		}
		else
			tmp.end++;
	}
	return (wc);
}

void	ft_transf_int_2(t_tmp *tmp, t_list *match, t_list *match2)
{
	tmp->lst = match;
	if (!access(tmp->lst->content, F_OK))
		ft_lstadd_back(&match2, ft_lstnew(ft_strdup(tmp->lst->content)));
	else if (!access(ft_trijoin(tmp->path, "/", tmp->lst->content, 2), F_OK))
		ft_lstadd_back(&match2, ft_lstnew(ft_strdup(tmp->lst->content)));
}

int	ft_transf_int(char *line)
{
	t_tmp	tmp;
	char	*pref;
	char	*suff;
	t_list	*match;
	t_list	*match2;

	match2 = NULL;
	tmp.i = 0;
	tmp.tab = ft_split4(line, "/");
	ft_transf2(&tmp, &suff, &pref);
	match = ft_wcfile(tmp.str, getcwd(tmp.path, PATH_MAX), 0, 0);
	if (ft_lstsize(match) > 1 || ft_lstsize(match) < 1)
	{
		ft_lstclear(&match, free);
		return (0);
	}
	tmp.lst->content = ft_trijoin(pref, tmp.lst->content, suff, 2);
	ft_transf_int_2(&tmp, match, match2);
	ft_lstclear(&match, free);
	if (match2)
	{
		ft_lstclear(&match2, free);
		return (1);
	}
	return (0);
}
