/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_chwc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:26:38 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/04/25 15:39:54 by lyaiche          ###   ########.fr       */
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
