/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdollar_hd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:46:04 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/25 15:39:54 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_chdollar_ok_hd(char *line);
char	*ft_changedollar_hd(char *line, t_list **dollar);

void	ft_chdollar_len_hd_2(t_tmp *tmp, char *line, t_list **dollar)
{
	tmp->lstart = tmp->i++;
	if (ft_strchr("\'\"", line[tmp->i]) && ++tmp->i)
		tmp->lcount--;
	else if (line[tmp->i] == '?' || ft_isdigit(line[tmp->i]))
	{
		tmp->lcount += -2;
		tmp->lcount += ft_strlen(ft_changedollar_hd(ft_substr(line,
						tmp->lstart, tmp->lend - tmp->lstart), dollar));
	}
	else
	{
		while (line[tmp->i] && (ft_isalnum(line[tmp->i])
				|| ft_strchr("?", line[tmp->i])))
			tmp->i++;
		tmp->lend = tmp->i;
		tmp->lcount += tmp->lstart - tmp->lend;
		tmp->lcount += ft_strlen(ft_changedollar_hd(ft_substr(line,
						tmp->lstart, tmp->end - tmp->lstart), dollar));
	}
}

size_t	ft_chdollar_len_hd(char *line, t_list **dollar)
{
	t_tmp	tmp;

	tmp.i = 0;
	tmp.lcount = 0;
	while (line[tmp.i])
	{	
		if (line[tmp.i] && line[tmp.i + 1] && line[tmp.i] == '$'
			&& (ft_isalnum(line[tmp.i + 1]) || ft_strchr("?", line[tmp.i + 1])))
			ft_chdollar_len_hd_2(&tmp, line, dollar);
		else
			tmp.i++;
	}
	return (tmp.i + tmp.lcount);
}

void	ft_chdollar_str_hd_2(t_tmp *tmp, char *line, char *str, t_list **dollar)
{
	if ((line[tmp->i] == '?' || ft_isdigit(line[tmp->i])) && ++tmp->i)
	{
		tmp->i2 = ft_strlcat(str, (*dollar)->content, tmp->len);
		*dollar = ft_next(*dollar);
	}
	else
	{
		while (line[tmp->i] && (ft_isalnum(line[tmp->i])
				|| ft_strchr("?", line[tmp->i])))
			tmp->i++;
		tmp->i2 = ft_strlcat(str, (*dollar)->content, tmp->len);
		*dollar = ft_next(*dollar);
	}
}

char	*ft_chdollar_str_hd(char *str, char *line, t_list *dollar, size_t len)
{
	t_tmp	tmp;

	tmp.i = 0;
	tmp.i2 = 0;
	tmp.len = len;
	while (line[tmp.i])
	{
		if (line[tmp.i] && line[tmp.i + 1] && line[tmp.i] == '$'
			&& (ft_isalnum(line[tmp.i + 1])
				|| ft_strchr("?", line[tmp.i + 1])) && ++tmp.i)
			ft_chdollar_str_hd_2(&tmp, line, str, &dollar);
		else if (line[tmp.i] && line[tmp.i] == '$' && line[tmp.i + 1]
			&& ft_strchr("\'\"", line[tmp.i + 1]))
			tmp.i++;
		else if (line[tmp.i])
		{
			str[tmp.i2++] = line[tmp.i++];
		}
	}
	str[tmp.i2] = 0;
	return (str);
}

char	*ft_chdollar_hd(char *line)
{
	size_t	len;
	char	*str;
	t_list	*dollar;

	if (!line)
		return (0);
	if (ft_chdollar_ok_hd(line))
		return (line);
	dollar = 0;
	len = ft_chdollar_len_hd(line, &dollar);
	str = ft_calloc(sizeof(*str), len + 1);
	str = ft_chdollar_str_hd(str, line, dollar, len);
	free(line);
	return (str);
}

// important les $ dans les here_doc 