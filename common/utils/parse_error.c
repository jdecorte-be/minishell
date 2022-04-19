/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:57:04 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/10 16:45:26 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parsing_redirect(char *line, size_t i);
int	ft_check_p_ok(char *line, size_t i);
int	ft_p_unexpected(char *line, size_t end);
int	ft_parse_error(int e);

int	ft_isprohibited_2_1(char *line, size_t *i)
{
	if (line[(*i) + 2] == ')'
		&& (!line[ft_next_word(line, ft_after_p(line, *i))]
			|| ft_strchr("&|", line[ft_next_word(line, *i)])))
		return (ft_parse_error(2));
	else if (line[ft_next_word(line, ft_after_p(line, *i))] && !ft_strchr("&|",
			line[ft_next_word(line, ft_after_p(line, *i))]))
		return (ft_p_unexpected(line, ft_next_word(line, *i)));
	return (0);
}

int	ft_next_p(char *line, size_t i)
{
	while (line[i] && line[i] != ')')
		i++;
	if (line[i] == ')')
		return (1);
	return (0);
}

void	ope_quotes(int *quote, char *line, size_t *i)
{
	char	c;

	(*quote)++;
	c = line[(*i)++];
	while (line[*i] && line[*i] != c)
		(*i)++;
	if (line[*i] && line[*i] == c)
		(*quote)++;
}

int	ft_isprohibited_2(char *line, size_t *i, int *quote, int *par)
{
	if (ft_strchr("\'\"", line[*i]))
		ope_quotes(quote, line, i);
	else if (ft_strchr("\\;", line[*i]))
		return (ft_parse_error(1));
	else if (ft_strchr("<>", line[*i]))
	{
		if (ft_parsing_redirect(line, *i) > 0)
			return (1);
	}
	else if ((!(*i) || ft_isspace(line[(*i) - 1])) && ft_check_p_ok(line, *i))
		return (1);
	else if (line[*i] == '(' && ++(*par)
		&& line[(*i) + 1] && ft_next_p(line, *i))
		return (ft_isprohibited_2_1(line, i));
	else if (line[*i] == ')' && (--(*par) < 0))
		return (ft_parse_error(2));
	return (0);
}

int	ft_isprohibited(char *line)
{
	size_t	i;
	int		quote;
	int		par;

	if (!line)
		return (0);
	i = 0;
	par = 0;
	quote = 0;
	if (!ft_strncmp("&&", line, 1))
		return (ft_parse_error(3));
	else if (!ft_strncmp("||", line, 1))
		return (ft_parse_error(4));
	else if (line[i] == '|')
		return (ft_parse_error(5));
	while (line[i])
	{
		if (ft_isprohibited_2(line, &i, &quote, &par))
			return (1);
		i++;
	}
	if (quote % 2 != 0 || par)
		return (ft_parse_error(1));
	return (0);
}
