/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:54:36 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/02 15:01:45 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_p_unexpected(char *line, size_t end)
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
	return (1);
}

int	ft_parse_error(int e)
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
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		g_data->lastret = 2;
		return (1);
	}
	g_data->lastret = 258;
	return (1);
}
