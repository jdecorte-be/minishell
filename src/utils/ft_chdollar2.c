/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdollar2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:53:21 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/04/22 17:59:23 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_changedollar(char *line, t_list **dollar)
{
	char	*str;

	if (ft_isdigit(line[0]))
		str = 0;
	else if (ft_strncmp(line, "$?", 1))
		str = ft_strdup(getenv(line + 1));
	else if (!ft_strncmp(line, "$?", 1))
		str = ft_itoa(g_data->lastret);
	else
		str = 0;
	ft_lstadd_back(dollar, ft_lstnew(str));
	free(line);
	return (str);
}

void	ft_chdollar_len_2_1(t_tmp *tmp, char *line, t_list **dollar)
{
	tmp->lstart = tmp->i++;
	if (line[tmp->i] && line[tmp->i] != '\"' && (line[tmp->i] == '?'
			|| ft_isdigit(line[tmp->i])) && ++tmp->i)
	{
		tmp->lend = tmp->i;
		tmp->lcount += tmp->lstart - tmp->lend;
		tmp->lcount += ft_strlen(ft_changedollar(ft_substr(line,
						tmp->lstart, tmp->lend - tmp->lstart), dollar));
	}
	else if (line[tmp->i] != '\"')
	{
		while (line[tmp->i] && line[tmp->i] != '\"'
			&& (ft_isalnum(line[tmp->i])
				|| ft_strchr("?", line[tmp->i])))
			tmp->i++;
		tmp->lend = tmp->i;
		tmp->lcount += tmp->lstart - tmp->lend;
		tmp->lcount += ft_strlen(ft_changedollar(
					ft_substr(line, tmp->lstart,
						tmp->lend - tmp->lstart), dollar));
	}
}

void	ft_chdollar_len_2(t_tmp *tmp, char *line, t_list **dollar)
{
	if (line[tmp->i] == '\'')
		ft_skip_q(line, &tmp->i);
	else if (line[tmp->i] == '\"' && ++tmp->i)
	{
		while (line[tmp->i] && line[tmp->i] != '\"')
		{
			while (line[tmp->i] && line[tmp->i] != '\"' && line[tmp->i] != '$')
				tmp->i++;
			if (line[tmp->i] && line[tmp->i] != '\"' && line[tmp->i + 1]
				&& line[tmp->i] == '$' && (ft_isalnum(line[tmp->i + 1])
					|| ft_strchr("?", line[tmp->i + 1])))
				ft_chdollar_len_2_1(tmp, line, dollar);
			else if (line[tmp->i] && line[tmp->i] != '\"')
				tmp->i++;
		}
		if (line[tmp->i])
			tmp->i++;
	}
}

void	ft_chdollar_len_3(t_tmp *tmp, char *line, t_list **dollar)
{
	tmp->lstart = tmp->i++;
	if (ft_strchr("\'\"", line[tmp->i]) && ++tmp->i)
		tmp->lcount--;
	else if (line[tmp->i] == '?' || ft_isdigit(line[tmp->i]))
	{
		tmp->lcount += -2;
		tmp->lcount += ft_strlen(ft_changedollar(ft_substr(line,
						tmp->lstart, tmp->lend - tmp->lstart), dollar));
	}
	else
	{
		while (line[tmp->i] && (ft_isalnum(line[tmp->i])
				|| ft_strchr("?", line[tmp->i])))
			tmp->i++;
		tmp->lend = tmp->i;
		tmp->lcount += tmp->lstart - tmp->lend;
		tmp->lcount += ft_strlen(ft_changedollar(ft_substr
					(line, tmp->lstart, tmp->lend - tmp->lstart), dollar));
	}
}

size_t	ft_chdollar_len(char *line, t_list **dollar)
{
	t_tmp	tmp;

	tmp.i = 0;
	tmp.lcount = 0;
	while (line[tmp.i])
	{
		if (ft_strchr("\'\"", line[tmp.i]))
			ft_chdollar_len_2(&tmp, line, dollar);
		else if (line[tmp.i] && line[tmp.i + 1] && line[tmp.i] == '$'
			&& (ft_isalnum(line[tmp.i + 1]) || ft_strchr("?", line[tmp.i + 1])))
			ft_chdollar_len_3(&tmp, line, dollar);
		else
			tmp.i++;
	}
	return (tmp.i + tmp.lcount);
}
