#include "../../inc/minishell.h"

int	ft_wc_in_fw(char *line)
{
	size_t	i;
	char	c;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i] && !ft_isspace(line[i]))
	{
		if (ft_strchr("\"\'", line[i]))
		{
			c = line[i++];
			while (line[i] && !ft_isspace(line[i]) && line[i] != c)
				i++;
			if (line[i] && !ft_isspace(line[i]))
				i++;
		}
		else if (line[i] == '*')
			return (0);
		else
			i++;
	}

	return (1);
}