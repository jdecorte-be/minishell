#include "../inc/minishell.h"

int lastpriority(char **input, int i)
{
	int tmp = i;
	while((input[tmp][0] != '(' || input[tmp][0] != ')') && input[tmp])
		tmp--;
	if(input[tmp][0] == '(')
		return 1;
	if(input[tmp][0] == ')')
		return 2;
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
			data->lastret = cmdlexer(input[i], d_env);
		else if(ft_strcmp(input[i], "(") == 0)
			data->isprio += 1;
		else if(ft_strcmp(input[i], ")") == 0)
			data->isprio -= 1;
		else if((ft_strcmp(input[i - 1], "&&") == 0 && data->lastret == 0))
			data->lastret = cmdlexer(input[i], d_env);
		else if(ft_strcmp(input[i - 1], "||") == 0 && data->lastret != 0)
			data->lastret = cmdlexer(input[i], d_env);
		else if(ft_strcmp(input[i - 1], "|") != 0)
			data->lastret = pipe_handler(d_env, input);
		else if(ft_strcmp(input[i - 1], "&&") != 0 && ft_strcmp(input[i - 1], "||") != 0)
			data->lastret = cmdlexer(input[i], d_env);

		i++;
		start = 0;
	}
	return data->lastret ;
}
