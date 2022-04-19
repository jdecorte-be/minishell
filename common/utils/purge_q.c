/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purge_q.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:59:27 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/03 16:06:36 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_purge_q_2(char *line, size_t *start, size_t *end, char *str)
{
	*start = *end;
	if (ft_strchr("\'\"", line[*end]) && line[*end + 1]
		&& line[*end + 1] == line[*end])
	{
		*end += 2;
		*start = *end;
	}
	else if (ft_strchr("\'\"", line[*end]))
	{
		ft_skip_q(line, end);
	}
	else
	{
		while (line[*end] && !ft_strchr("\'\"", line[*end]))
			*end += 1;
	}
	if (*start != *end)
		str = ft_strjoin2(str, ft_substr(line, *start, *end - *start));
}

char	*ft_purge_q(char *line)
{
	size_t	end;
	size_t	start;
	char	*str;

	end = 0;
	str = 0;
	while (line[end])
		ft_purge_q_2(line, &start, &end, str);
	printf("str == %s\n", str);
	return (str);
}
