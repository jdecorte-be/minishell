#include "../../inc/minishell.h"

int	ft_parsing_redirect(char *line, size_t i)
{
	int a;

	a = 0;
	i = ft_next_word(line, i);
	if (line[i] == '<' && ++a)
		write(2, "bash: syntax error near unexpected token `<'\n", 46);
	else if (line[i] == '>' && ++a)
		write(2, "bash: syntax error near unexpected token `>'\n", 46);
	return (a);
}

void	ft_parse_error(int e)
{
	if (e == 1)
		write(2, "prohibited character or input not close\n", 40);
	else if (e == 2)
		write(2, "syntax error near unexpected token `)'\n", 39);
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
		else if (line[i] == '(')
			par++;
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