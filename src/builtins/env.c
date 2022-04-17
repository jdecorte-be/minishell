# include "../../inc/minishell.h"

int checkvalid(char *cmd)
{
    int i = 0;
    while(cmd[i])
    {
		if(cmd[0] != '=' && cmd[i] == '=')
			return -1;
        else if((ft_isalnum(cmd[i]) == 0 && cmd[i] != '\'' && cmd[i] != '"' && cmd[i] != '_') || ft_isdigit(cmd[0]) == 1)
        {
            printf("minishell: unset: %s: not a valid identifier\n", cmd);
            return 0;
        }
        i++;
    }
    return 1;
}

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
		if (strncmp(c, name, len) == 0 && c[len] == '=') {
			*offset = p - environ;
			return (c + len + 1);
		}
        ++p;
    }
	return (NULL);
}

int my_setenv(char *name, char *value)
{
	static char **lastenv;
	char *C;
	int l_value, offset;

	if (*value == '=')
		++value;
	l_value = ft_strlen(value);
	if ((C = findenv(name, &offset)))
    {
		if ((int)ft_strlen(C) >= l_value)
        {
			while ((*C++ = *value++))
				;
			return (0);
		}
	}
    else
    {					/* create new slot */
		size_t cnt;
		char **P;
		for (P = data->env ; *P != NULL; P++)
			;
		cnt = P - data->env ;
        P = (char **)ft_realloc(lastenv, sizeof(char *) * (cnt + 2));
		if (!P)
			return (-1);
		if (lastenv != data->env )
			memcpy(P, data->env , cnt * sizeof(char *));
		lastenv = data->env  = P;
		offset = cnt;
		data->env [cnt + 1] = NULL;
	}
    C = (char *)name;
    while(*C && *C != '=')
        ++C;
	if (!(data->env [offset] =			/* name + `=' + value */
	    malloc((size_t)((int)(C - name) + l_value + 2))))
		return (-1);
	for (C = data->env [offset]; (*C = *name++) && *C != '='; ++C)
		;
	for (*C++ = '='; (*C++ = *value++); )
		;
	return (0);
}

char *my_getenv(char *name, t_data *data)
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

