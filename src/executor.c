#include "../inc/minishell.h"

int have_pipe(char *cmd)
{
	int i = 0;

	while(cmd[i])
	{
		if(cmd[i] == '|' && cmd[i + 1] && cmd[i + 1] != '|')
			return 1;
		i++;
	}
	return 0;
}

int executeur(char *input, t_env *d_env)
{
	if(have_pipe(input))
		return pipe_handler(d_env, ft_split(input, "|"));
	else
		return cmdlexer(input, d_env);
	return -1;
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
			data->lastret = executeur(input[i], d_env);
		else if(start == 0 && ft_strcmp(input[i - 1], "&&") == 0 && data->lastret == 0 && ft_strcmp(input[i], "(") && ft_strcmp(input[i], ")"))
			data->lastret = executeur(input[i], d_env);
		else if(start == 0 && ft_strcmp(input[i - 1], "||") == 0 && data->lastret != 0 && ft_strcmp(input[i], "(") && ft_strcmp(input[i], ")"))
			data->lastret = executeur(input[i], d_env);
		else if(ft_strcmp(input[i - 1], "(") == 0)
			data->lastret = subshell(input[i], d_env, data);
		// printf("---> %d\n", data->lastret);


		i++;
		start = 0;
	}
	return data->lastret ;
}
