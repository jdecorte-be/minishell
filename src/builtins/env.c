# include "../../inc/minishell.h"

char *findenv(char *name, int *offset)
{
	int len;
	const char *np;
	char **p, *c;
    char **environ = data->env;

	if (name == NULL || environ == NULL)
		return (NULL);
    np = name;
    while(*np && *np != '=')
        ++np;
	len = np - name;
    p = environ;
    while((c = *p) != NULL)
    {
		if (strncmp(c, name, len) == 0 && c[len] == '=')
		{
			*offset = p - environ;
			return (c + len + 1);
		}
        ++p;
    }
	return (NULL);
}

int my_setenv(char *var)
{
	char *name = ft_substr(var, 0, egal_len(var));
	char *value;
	if(var[egal_len(var)] == '=')
		value = ft_substr(var, egal_len(var) + 1, ft_strlen(var));
	else
		value = ft_strdup("\0");
	
	static char **lastenv;
	char *C;
	int l_value, offset;

	l_value = ft_strlen(value);
	if ((C = findenv(name, &offset)))
    {
		if ((int)ft_strlen(C) >= l_value)
        {
			ft_strlcpy(C,  value, ft_strlen(C));
			return (0);
		}
	}
    else
    {
		size_t cnt;
		char **P = data->env;
		while (*P != NULL)
			P++;
		cnt = P - data->env ;
        P = ft_realloc(lastenv, sizeof(char *) * (cnt + 2));
		if (!P)
			return (-1);
		if (lastenv != data->env )
			ft_memcpy(P, data->env , cnt * sizeof(char *));
		lastenv = data->env  = P;
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

char *my_getenv(char *name)
{
    int i = 0;

    while(data->env[i])
    {
        int j = 0;
        while(data->env[i][j] && data->env[i][j] != '=')
            j++;
        if(ft_strcmp(ft_substr(data->env[i], 0, j), name) == 0)
            return ft_substr(data->env[i], j + 1, ft_strlen(data->env[i]));
        i++;
    }
    return NULL;
}

