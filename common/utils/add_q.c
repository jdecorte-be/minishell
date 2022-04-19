/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_q.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:30:41 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/02 12:46:45 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_q_str_2_2(char **str, char *line, size_t *end, t_tmp *tmp)
{
	while (line[*end] && !ft_isspace(line[*end])
		&& !ft_strchr("\'\"", line[*end]) && tmp->c == 0)
		(*end)++;
	if (*end != tmp->start)
	{
		*str = ft_quajoin(*str, "\"", ft_substr(line,
					tmp->start, *end - tmp->start), "\"");
		tmp->start = *end;
	}
	if (line[*end] && ft_strchr("\'\"", line[*end]))
		tmp->c = line[(*end)++];
}

void	ft_add_q_str_2(char **str, char *line, size_t *end, t_tmp *tmp)
{
	if (tmp->c != 0)
	{
		while (line[*end] && line[*end] != tmp->c)
			(*end)++;
		if (line[*end])
		{
			(*end)++;
			tmp->c = 0;
		}
		*str = ft_strjoin3(*str,
				ft_substr(line, tmp->start, *end - tmp->start));
		tmp->start = *end;
	}
	else if (line[*end] && !ft_isspace(line[*end]) && tmp->c == 0)
		ft_add_q_str_2_2(str, line, end, tmp);
}

void	ft_add_q_str_3(char *line, size_t *end, t_tmp *tmp)
{
	if (line[*end] && !ft_isspace(line[*end])
		&& ft_strchr("\'\"", line[*end]) && tmp->c != 0)
	{
		tmp->c = 0;
		(*end)++;
	}
	else if (line[*end] && !ft_isspace(line[*end])
		&& ft_strchr("\'\"", line[*end]) && tmp->c == 0)
		tmp->c = line[(*end)++];
	else
		(*end)++;
}

char	*ft_add_q_str(char **str, char *line, size_t *end)
{
	t_tmp	tmp;

	tmp.c = 0;
	while (line[*end])
	{
		tmp.start = *end;
		while (line[*end] && line[*end] != '=')
			ft_add_q_str_3(line, end, &tmp);
		*str = ft_strjoin3(*str, ft_substr(line, tmp.start,
					*end - tmp.start + 1));
		tmp.start = *end;
		if (line[*end] && line[*end] == '=' && ++(*end))
		{
			tmp.start = *end;
			while (line[*end] && (!ft_isspace(line[*end]) || tmp.c))
				ft_add_q_str_2(str, line, end, &tmp);
		}		
	}
	return (*str);
}

char	*ft_add_q_dollar(char *line)
{
	size_t	end;
	size_t	start;
	char	*str;

	if (!line)
		return (line);
	end = 0;
	str = 0;
	while (line[end])
	{
		start = end;
		if (!ft_strncmp(line + end, "export ", 6))
		{
			end = ft_next_word(line, end);
			str = ft_strjoin3(str, ft_substr(line, start, end - start));
			while (line[end] && !ft_strchr("&|", line[end]))
			{
				str = ft_add_q_str(&str, line, &end);
				end = ft_next_word(line, end);
			}
		}
		else
			return (line);
	}
	return (str);
}
