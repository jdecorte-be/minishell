/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ecrase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:49:33 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/25 15:39:54 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_ecrase_q2(char *word, t_tmp *tmp)
{
	tmp->c = 0;
	tmp->start = tmp->end;
	if (word[tmp->end] && ft_strchr("\'\"", word[tmp->end]))
	{
		tmp->c = word[tmp->end++];
		tmp->start = tmp->end;
		while (word[tmp->end] && word[tmp->end] != tmp->c)
			tmp->end++;
		tmp->str = ft_strjoin3(tmp->str, ft_substr(word, tmp->start,
					tmp->end - tmp->start));
		if (word[tmp->end])
			tmp->end++;
	}
	else
	{
		while (word[tmp->end] && !ft_strchr("\'\"", word[tmp->end]))
			tmp->end++;
		tmp->str = ft_strjoin3(tmp->str, ft_substr(word,
					tmp->start, tmp->end - tmp->start));
	}
}

char	*ft_ecrase_q(char *word)
{
	t_tmp	tmp;

	if (!word)
		return (0);
	tmp.end = 0;
	tmp.str = 0;
	while (word[tmp.end])
		ft_ecrase_q2(word, &tmp);
	return (tmp.str);
}

void	ft_ecrase_p2(t_tmp *tmp, char *line)
{
	tmp->start = tmp->end;
	if (line[tmp->end] && ft_strchr("\"\'", line[tmp->end]))
	{
		ft_skip_q(line, &tmp->end);
		tmp->str = ft_strjoin3(tmp->str,
				ft_substr(line, tmp->start, tmp->end - tmp->start));
	}
	else if (line[tmp->end] && line[tmp->end] == '(')
	{
		ft_skip_p(line, &tmp->end);
		tmp->start += 2;
		tmp->str = ft_strjoin3(tmp->str, ft_substr(line,
					tmp->start, tmp->end - tmp->start - 2));
	}
	else
	{
		while (line[tmp->end]
			&& line[tmp->end] != '(' && !ft_strchr("\"\'", line[tmp->end]))
			tmp->end++;
		tmp->str = ft_strjoin3(tmp->str,
				ft_substr(line, tmp->start, tmp->end - tmp->start));
	}
}

char	*ft_ecrase_p(char *line)
{
	t_tmp	tmp;

	if (!line)
		return (line);
	tmp.str = 0;
	tmp.end = 0;
	while (line[tmp.end])
		ft_ecrase_p2(&tmp, line);
	return (tmp.str);
}
