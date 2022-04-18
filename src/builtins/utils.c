# include "../../inc/minishell.h"
#include <malloc/malloc.h>

void *ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	ft_memcpy(new_ptr, ptr, size);
	return (new_ptr);
}

int print_env(char **env)
{
	int i = 0;
	while(env[i])
    {
        if(env[i][egal_len(env[i])] == '=')
        {
            ft_putstr_fd(env[i], 1);
            ft_putstr_fd("\n", 1);
        }
        i++;
    }
	return 0;
}

void format_env(char *var)
{
    ft_putstr_fd("declare -x ", 1);
    ft_putstr_fd(ft_substr(var, 0, egal_len(var)), 1);
    if(var[egal_len(var)] == '=')
    {
        ft_putstr_fd("=\"", 1);
        ft_putstr_fd(ft_substr(var, egal_len(var) + 1, ft_strlen(var)), 1);
        ft_putstr_fd("\"", 1);
    }
    ft_putstr_fd("\n", 1);
}

int egal_len(char *cmd)
{
    int i = 0;
    while(cmd[i] && cmd[i] != '=')
        i++;
    return i;
}
