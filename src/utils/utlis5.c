#include "../../inc/minishell.h"

int	ft_next_word(char *line, size_t i)
{
	char	c;

	while (line[i] && !ft_isspace(line[i]))
	{
		if (ft_strchr("\"\'", line[i]))
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				i++;
			if (line[i])
				i++;
		}
		else
			i++;
	}
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

int	ft_next_cmd(char *line, size_t i)
{
	while (line[i] && !ft_strchr("|&", line[i]))
		i++;
	while (line[i] && (ft_strchr("|&", line[i]) || ft_isspace(line[i])))
		i++;
	return (i);
}
