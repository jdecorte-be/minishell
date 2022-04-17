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

int my_setenv(char *name, char *value, t_data *data)
{
	static char **lastenv;			/* last value of environ */
	char *C;
	int l_value, offset;
	size_t cnt;
	char **P = data->env;

	l_value = ft_strlen(value);
	if ((C = getenv(name)))
    {
        ft_strlcpy(C, value, ft_strlen(value) + 1);
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

