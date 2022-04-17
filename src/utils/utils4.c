#include "../../inc/minishell.h"

int	ft_strstrchr(char *str, char *set)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(set, str[i]))
			return (str[i]);
	}
	return (0);
}