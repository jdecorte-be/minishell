# include "../../inc/minishell.h"

int my_setenv(char *var)
{
	int l_value, offset;
	char *C;
	static char **lastenv;
	char *name;
	char *value;
	size_t cnt;
	char **P = data->env;

	name = ft_substr(var, 0, egal_len(var));
	if(var[egal_len(var)] == '=')
		value = ft_substr(var, egal_len(var) + 1, ft_strlen(var));
	else
		value = ft_strdup("\0");
	

	l_value = ft_strlen(value);
	C = my_getenv(name, &offset);
	printf("%s %d\n", C, offset);
	if (C)
    {
		if ((int)ft_strlen(C) >= l_value)
        {
			ft_strlcpy(C,  value, ft_strlen(C));
			return (0);
		}
	}
    else
    {
		while (*P)
			P++;
		cnt = splitlen(data->env);
        P = ft_realloc(lastenv, sizeof(char *) * (cnt + 2));
		if (!P)
			return (-1);
		if (lastenv != data->env)
			ft_memcpy(P, data->env , cnt * sizeof(char *));
		lastenv = P;
		offset = cnt;
		data->env [cnt + 1] = NULL;
	}
    C = name;
    while(*C && *C != '=')
        ++C;
	if (!(data->env[offset] = ft_calloc(1, (size_t)((int)(C - name) + l_value + 2))))
		return (-1);
    C = data->env[offset];
	while((*C = *name++) && *C != '=')
        ++C;
	if(var[egal_len(var)] == '=')
		*C++ = '=';
	while((*C++ = *value++));
	return (0);
}

char *my_getenv(char *name, int *index)
{
    int i = 0;

    while(data->env[i])
    {
        int j = 0;
        while(data->env[i][j] && data->env[i][j] != '=')
            j++;
        if(ft_strcmp(ft_substr(data->env[i], 0, j), name) == 0)
		{
			if(index != NULL)
				*index = i;
            return ft_substr(data->env[i], j + 1, ft_strlen(data->env[i]));
		}
        i++;
    }
    return NULL;
}

