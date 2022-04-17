#include "../inc/minishell.h"

int check_ope(char *ope)
{
    if(ft_strcmp(ope, "&&") == 0)
        return 1;
    if(ft_strcmp(ope, "||") == 0)
        return 2;
    if(ft_strcmp(ope, "|") == 0)
        return 3;
    return 0;
}

int execute(char **input, t_data *data, t_env *d_env)
{
	int i = 0;
	int start = 1;

	if (!input || !*input)
		return (0);
	while(input[i])
	{
		if(start == 1)
			data->lastret = cmdlexer(input[i], d_env);
		else if(ft_strcmp(input[i - 1], "&&") == 0 && data->lastret == 0)
			data->lastret = cmdlexer(input[i], d_env);
		else if(ft_strcmp(input[i - 1], "||") == 0 && data->lastret != 0)
			data->lastret = cmdlexer(input[i], d_env);
		

		i++;
		start = 0;
	}
	return 0;
}