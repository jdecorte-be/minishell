/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_q.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:30:41 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 18:32:55 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_add_q_str(char *str, char *line, size_t *end)
{
	int		trig;
	char	c;
	size_t	start;
	char	*s1;
	size_t	i;

	trig = 0;
	c = 0;
	while (line[*end])
	{
		start = *end;
		while (line[*end] && line[*end] != '=')
		{
			if (line[*end] && !ft_isspace(line[*end])
				&& ft_strchr("\'\"", line[*end]) && c != 0)
			{
				c = 0;
				(*end)++;
			}
			else if (line[*end] && !ft_isspace(line[*end])
				&& ft_strchr("\'\"", line[*end]) && c == 0)
			{
				c = line[(*end)++];
			}
			else
				(*end)++;
		}
		str = ft_strjoin1(str, ft_substr(line, start, *end - start + 1));
		start = *end;
		if (line[*end] && line[*end] == '=' && ++(*end))
		{
			start = *end;
			while (line[*end] && (!ft_isspace(line[*end]) || c))
			{
				if (c != 0)
				{
					while (line[*end] && line[*end] != c)
					{
						(*end)++;
					}
					if (line[*end])
					{
						(*end)++;
						c = 0;
					}
					str = ft_strjoin1(str,
							ft_substr(line, start, *end - start));
					start = *end;
				}
				else if (line[*end] && !ft_isspace(line[*end]) && c == 0)
				{
					while (line[*end] && !ft_isspace(line[*end])
						&& !ft_strchr("\'\"", line[*end]) && c == 0)
					{
						(*end)++;
					}
					if (*end != start)
					{
						str = ft_quajoin(str, "\"",
								ft_substr(line, start, *end - start), "\"");
						start = *end;
					}
					if (line[*end] && ft_strchr("\'\"", line[*end]))
					{
						c = line[(*end)++];
					}
				}
			}
		}		
	}
	return (str);
}

char	*ft_add_q_dollar(char *line)
{
	size_t	end;
	size_t	start;
	char	*str;
	int		trig;
	char	c;

	if (!line)
		return (line);
	trig = 0;
	end = 0;
	str = 0;
	while (line[end])
	{
		start = end;
		if (!ft_strncmp(line + end, "export ", 6))
		{
			end = ft_next_word(line, end);
			str = ft_strjoin1(str, ft_substr(line, start, end - start));
			while (line[end] && !ft_strchr("&|", line[end]))
			{
				str = ft_add_q_str(str, line, &end);
				end = ft_next_word(line, end);
			}
		}
		else
			return (line);
	}
	return (str);
}
