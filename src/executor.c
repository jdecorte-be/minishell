#include "../inc/minishell.h"

int what_im(char *input)
{
	if(ft_strcmp(input, "&&") == 0)
		return 1;
	else if(ft_strcmp(input, "||") == 0)
		return 2;
	else if(ft_strcmp(input, "|") == 0)
		return 3;
	else if(ft_strcmp(input, "<") == 0)
		return 4;
	else if(ft_strcmp(input, ">") == 0)
		return 5;
	else if(ft_strcmp(input, "(") == 0)
		return 4;
	else if(ft_strcmp(input, ")") == 0)
		return 5;
	return 0;
}

int what_before(char **input, int i)
{
	while(input[i])
	{
		if(ft_strcmp(input[i], "&&") == 0)
			return 1;
		else if(ft_strcmp(input[i], "||") == 0)
			return 2;
		else if(ft_strcmp(input[i], "|") == 0)
			return 3;
		else if(ft_strcmp(input[i], "<") == 0)
			return 4;
		else if(ft_strcmp(input[i], ">") == 0)
			return 5;
		i--;
	}
	return 0;
}

int pipe_is_after(char **input, int i)
{
	while(input[i])
	{
		if(ft_strcmp(input[i], "&&") == 0)
			return 0;
		if(ft_strcmp(input[i], "||") == 0)
			return 0;
		if(ft_strcmp(input[i], "|") == 0)
			return 1;
		i++;
	}
	return 0;
}

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

int check_pipe(t_data *data, char **input, int *i, int shell)
{
	if(pipe_is_after(input, *i))
		pipe_handler(data, input, *i);
	else if (shell == 0)
		cmdlexer(input[*i], data);
	else if (shell == 1)
		subshell(input[*i], data);
}


int execute(char **input, t_data *data)
{
	int i = 0;
	int start = 1;
	if (!input || !*input)
		return (0);
	while(input[i])
	{
		// start
		if(start == 1 && what_im(input[i]) == 0)
			data->lastret = check_pipe(data, input, i, 0);
		// '&&' behind cmd
		else if(start == 0 && what_before(input, i) == 1 && what_im(input[i]) == 0 && data->lastret == 0)
			data->lastret = check_pipe(data, input, i, 0);
		// '||' behind cmd
		else if(start == 0 && what_before(input, i) == 2 && what_im(input[i]) == 0 && data->lastret != 0)
			data->lastret = check_pipe(data, input, i, 0);
		// '||' behind the parentheses cmd
		else if(ft_strcmp(input[i - 1], "(") == 0 && what_before(input, i) == 2 && what_im(input[i]) == 0 && data->lastret != 0)
			data->lastret = check_pipe(data, input, i, 1);
		// '&&' behind the parentheses cmd
		else if(ft_strcmp(input[i - 1], "(") == 0 && what_before(input, i) == 1 && what_im(input[i]) == 0 && data->lastret == 0)
			data->lastret = check_pipe(data, input, i, 1);




		// printf("---> %d\n", data->lastret);
		i++;
		start = 0;
	}
	return data->lastret ;
}
