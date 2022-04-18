# include "../../inc/minishell.h"

void *ft_realloc(void *str, size_t len)
{
    char *res;

    res = malloc(len);
    if(!res)
        return 0;
    if(!str)
        return malloc(len);
    if(len <= ft_strlen(str))
        return str;
    ft_memcpy(str, res, ft_strlen(str));
    free(str);
    return res;
}

int print_env(char **env)
{
	int i = 0;
	while(env[++i])
		printf("%s\n", env[i]);
	return 0;
}

int egal_len(char *cmd)
{
    int i = 0;
    while(cmd[i] && cmd[i] != '=')
        i++;
    return i;
}
