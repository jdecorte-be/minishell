/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:57:04 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 20:59:05 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_parsing_redirect(char *line, size_t i)
{
	int	a;

	a = 0;
	i = ft_next_word(line, i);
	if (!line[i] && ++a)
	{
		write(2, "minishell: syntax error near ", 29);
		write(2, "unexpected token `newline'\n", 27);
	}
	if (line[i] == '<' && ++a)
		write(2, "minishell: syntax error near unexpected token `<'\n", 51);
	else if (line[i] == '>' && ++a)
		write(2, "minishell: syntax error near unexpected token `>'\n", 51);
	if (a)
		g_data->lastret = 258;
	return (a);
}

int	ft_check_p_ok(char *line, size_t i)
{
	size_t	start;
	char	*str;

	start = i;
	if (!ft_strchr("&|", line[i]))
	{
		i = ft_next_word(line, i);
		if (line[i] && line[i] == '(')
		{
			str = ft_substr(line, start, i - start - 1);
			write(2, "minishell: syntax error near unexpected token `", 47);
			write(2, str, ft_strlen(str));
			write(2, "\'\n", 2);
			return (1);
		}
	}
	i = start;
	return (0);
}

void	ft_p_unexpected(char *line, size_t end)
{
	size_t	start;
	char	*str;

	start = end;
	while (line[end] && !ft_isspace(line[end]))
		end++;
	str = ft_substr(line, start, end - start);
	printf("%s\n", str);
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, str, ft_strlen(str));
	write(2, "\'\n", 2);
	g_data->lastret = 258;
}

void	ft_parse_error(int e)
{
	if (e == 1)
		write(2, "prohibited character or input not close\n", 40);
	else if (e == 2)
		write(2, "minishell: syntax error near unexpected token `)'\n", 50);
	else if (e == 3)
		write(2, "minishell: syntax error near unexpected token `&&'\n", 51);
	else if (e == 4)
		write(2, "minishell: syntax error near unexpected token `||'\n", 51);
	else if (e == 5)
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	g_data->lastret = 258;
}

int	ft_isprohibited(char *line)
{
	size_t	i;
	int		quote;
	char	c;
	int		par;

	if (!line)
		return (0);
	i = 0;
	par = 0;
	quote = 0;
	if (!ft_strncmp("&&", line, 1))
	{
		ft_parse_error(3);
		return (1);
	}
	else if (!ft_strncmp("||", line, 1))
	{
		ft_parse_error(4);
		return (1);
	}
	else if (line[i] == '|')
	{
		ft_parse_error(5);
		return (1);
	}
	while (line[i])
	{
		if (ft_strchr("\'\"", line[i]))
		{
			quote++;
			c = line[i++];
			while (line[i] && line[i] != c)
				i++;
			if (line[i] && line[i] == c)
				quote++;
		}
		else if (ft_strchr("\\;", line[i]))
			ft_parse_error(1);
		else if (ft_strchr("<>", line[i]))
		{
			if (ft_parsing_redirect(line, i) > 0)
				return (1);
		}
		else if ((!i || ft_isspace(line[i - 1])) && ft_check_p_ok(line, i))
		{
			return (1);
		}
		else if (line[i] == '(')
		{
			par++;
			if (line[i + 1] == ')' && (!line[ft_next_word(line, i)]
					|| ft_strchr("&|", line[ft_next_word(line, i)])))
			{
				ft_parse_error(2);
				return (1);
			}
			else if (line[ft_next_word(line, i)] && !ft_strchr("&|",
					line[ft_next_word(line, i)]))
			{
				ft_p_unexpected(line, ft_next_word(line, i));
				return (1);
			}
		}
		else if (line[i] == ')')
		{
			par--;
			if (par < 0)
			{
				ft_parse_error(2);
				return (1);
			}
		}
		i++;
	}
	if (quote % 2 != 0 || par)
	{
		ft_parse_error(1);
		return (1);
	}
	return (0);
}
