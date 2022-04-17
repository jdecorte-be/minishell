#include "../inc/minishell.h"

char *tokenize(char *line)
{
	size_t	i;
	int		par;
	char	c;
	
	if (!line)
		return (line);
	i = 0;
	par = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '(')
			ft_skip_p(line, &i);
		else if (line[i] && ft_strchr("\'\"", line[i]))
			ft_skip_q(line, &i);
		else if (line[i] && line[i + 1] && (ft_strnstr(line + i, "&&", 2) || ft_strnstr(line + i, "||", 2)))
		{
			if (i)
				line[i - 1] = 1;
			if (line[i + 2])
				line[i + 2] = 1;
			i += 2;
		}
		else if (line[i] && line[i] == '|')
		{
			if (i)
				line[i - 1] = 1;
			if (line[i + 1])
				line[i + 1] = 1;
			i++;
		}
		else
			i++;
	}
	return (line);
}