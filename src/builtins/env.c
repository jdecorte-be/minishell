# include "../../inc/minishell.h"

char **dont_exist(char **lastenv, int *index)
{
	char **P = data->env;
	int cnt;

	while (*P)
		P++;
	cnt = splitlen(data->env);
	P = ft_realloc(lastenv, sizeof(char *) * (cnt + 2));
	if (!P)
		return NULL;
	if (lastenv != data->env)
		ft_memcpy(P, data->env , cnt * sizeof(char *));
	*index = cnt;
	data->env [cnt + 1] = NULL;
	return P;
}


int my_setenv(char *var)
{
	int offset;
	char *C;
	static char **lastenv;
	char *name;
	char *value;
	int		e_len;

	e_len = egal_len(var);
	name = ft_substr(var, 0, e_len);
	if(var[e_len] == '=')
		value = ft_substr(var, e_len + 1, ft_strlen(var));
	else
		value = ft_strdup("\0");
	C = my_getenv(name, &offset);
	if (C)
	{
		if ((int)ft_strlen(C) >= ft_strlen(value))
		{
			while ((*C++ = *value++));
			return (0);
		}
	}
	else
		lastenv = dont_exist(lastenv, &offset);
	if (!(data->env[offset] = ft_calloc(1, (size_t)((e_len + ft_strlen(value) + 2)))))
		return (-1);
	C = data->env[offset];
	while((*C = *name++) && *C != '=')
		++C;
	if(var[e_len] == '=')
		*C++ = '=';
	while((*C++ = *value++));
	return (0);
}

// * Fix and Work
char *my_getenv(char *name, int *index)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while(data->env[i])
	{
		j = 0;
		while(data->env[i][j] && data->env[i][j] != '=')
			j++;
		sub = ft_substr(data->env[i], 0, j);
		if(ft_strcmp(sub, name) == 0)
		{
			free(sub);
			if(index != NULL)
				*index = i;
			return data->env[i] + j + 1;
		}
		free(sub);
		i++;
	}
	return (NULL);
}

