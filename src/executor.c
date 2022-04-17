#include "../inc/minishell.h"

int execute(char **input, t_data *data, t_env *d_env)
{
	int i = 0;
	int start = 1;
	if (!input || !*input)
		return (0);
	while(input[i])
	{
		if(start == 1 && (!input[i + 1] || ft_strcmp(input[i + 1], "|") != 0))
			data->lastret = cmdlexer(input[i], d_env);
		
		
		else if(start == 0 && ft_strcmp(input[i - 1], "&&") == 0 && data->lastret == 0)
			data->lastret = cmdlexer(input[i], d_env);
		
		
		else if(start == 0 && ft_strcmp(input[i - 1], "||") == 0 && data->lastret != 0)
			data->lastret = cmdlexer(input[i], d_env);
		
		
		else if(start == 0 && ft_strcmp(input[i - 1], "|") != 0)
			data->lastret = pipe_handler(d_env, input);
		
		
		// else if(start == 0 && ft_strcmp(input[i - 1], "&&") != 0 && ft_strcmp(input[i - 1], "||") != 0)
		// 	data->lastret = cmdlexer(input[i], d_env);


		i++;
		start = 0;
	}
	return data->lastret ;
}
