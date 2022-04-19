/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ecrase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:49:33 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/12 19:28:25 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_ecrase_q_2(char *word, size_t *start, size_t *end, char *new_word)
{
	char	c;

	c = 0;
	new_word = 0;
	*end = 0;
	*start = *end;
	if (word[*end] && ft_strchr("\'\"", word[*end]))
	{
		c = word[*end++];
		*start = *end;
		while (word[*end] && word[*end] != c)
			end++;
		new_word = ft_strjoin3(new_word,
				ft_substr(word, *start, end - start));
		if (word[*end])
			end += 1;
	}
	else
	{
		while (word[*end] && !ft_strchr("\'\"", word[*end]))
			*end += 1;
		new_word = ft_strjoin3(new_word,
				ft_substr(word, *start, *end - *start));
	}
}

char	*ft_ecrase_q(char *word)
{
	size_t	start;
	size_t	end;
	char	*new_word;

	if (!word)
		return (0);
	while (word[end])
	{
		ft_ecrase_q_2(word, &start, &end, new_word);
	}
	return (new_word);
}

char	*ft_ecrase_p(char *line)
{
	char	*str;
	size_t	start;
	size_t	end;

	if (!line)
		return (line);
	str = 0;
	end = 0;
	while (line[end])
	{
		start = end;
		if (line[end] && ft_strchr("\"\'", line[end]))
		{
			ft_skip_q(line, &end);
			str = ft_strjoin3(str, ft_substr(line, start, end - start));
		}
		else if (line[end] && line[end] == '(')
		{
			ft_skip_p(line, &end);
			start += 2;
			str = ft_strjoin3(str, ft_substr(line, start, end - start - 2));
		}
		else
		{
			while (line[end] && line[end] != '(' && !ft_strchr("\"\'", line[end]))
				end++;
			str = ft_strjoin3(str, ft_substr(line, start, end - start));
		}
	}
	return (str);
}
