#include "builtins.h"
#include <strings.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <crt_externs.h>

int env_len(char **env)
{
    int i = 0;
    while(env[i])
        i++;
    return i;
}

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

int my_setenv(char *name, char *value, t_env *data)
{
	static char **lastenv;			/* last value of environ */
	char *C;
	int l_value, offset;
	size_t cnt;
	char **P = data->env;

	l_value = ft_strlen(value);
	if ((C = getenv(name)))
    {
        ft_memcpy(C, value, ft_strlen(value));
        return (0);
	}
    else
    {
        while(*P)
            P++;
		cnt = P - data->env;
        P = (char **)ft_realloc(lastenv, sizeof(char *) * (cnt + 2));
		if (!P)
			return (-1);
		if (lastenv != data->env)
			ft_memcpy(P, data->env, cnt * sizeof(char *));
		lastenv = data->env = P;
		offset = cnt;
		data->env[cnt + 1] = NULL;
	}
	if (!(data->env[offset] = malloc((size_t)((int)(C - name) + l_value + 2))))
		return (-1);
	return (0);
}

void print_exp(char **env)
{
    int len = env_len(env);
    int i = 0;
    while(i < len)
    {
        int j = i+1;
        while (++j < len)
            if (ft_strcmp(env[i], env[j]) > 0 && env[i] && env[j]) {
                char* temp = env[i]; 
                env[i] = env[j]; 
                env[j] = temp; 
             }
             if(env[i])
                printf("declare -x %s\n", env[i]);
        i++;
    }
}

int repl_env(char **cmd)
{
    int i = 0;
    while(cmd[1][i] && cmd[1][i] != '=')
        i++;
    char *var = getenv(ft_substr(cmd[1], 0, i));
    printf("export %s\n", ft_substr(cmd[1], 0, i));
    ft_memcpy(var, ft_substr(cmd[1], i + 1, ft_strlen(cmd[1])), ft_strlen(var));
    return 0;
}

int export(char **cmd,t_env *data)
{
    if(!cmd[1])
    {
        print_exp(data->env);
        return 0;
    }
    int i = 0;
    while(cmd[1][i] && cmd[1][i] != '=')
        i++;
    char *var = getenv(ft_substr(cmd[1], 0, i));
    if(var)
        ft_memcpy(var, ft_substr(cmd[1], i + 1, ft_strlen(cmd[1])), ft_strlen(cmd[1]));
    else
        my_setenv(ft_substr(cmd[1], 0, i), ft_substr(cmd[1], i + 1, ft_strlen(cmd[1])), data);

    return 0;
}
