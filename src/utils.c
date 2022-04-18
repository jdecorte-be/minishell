#include "../inc/minishell.h"

void	puterror(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
	// exit(0);
}

void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

int splitlen(char **split)
{
	int i = 0;

	while(split[i] != NULL)
		i++;
	return i;
}