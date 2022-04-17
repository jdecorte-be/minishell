#include "../../inc/minishell.h"

int	ft_free(char *line)
{
	free(line);
	return (1);
}

int	ft_str_isspace(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}
