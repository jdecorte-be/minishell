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
	int j = i;

	while(input[j])
	{
		if(ft_strcmp(input[j], "&&") == 0)
			return 0;
		if(ft_strcmp(input[j], "||") == 0)
			return 0;
		if(ft_strcmp(input[j], "|") == 0)
			return 1;
		j++;
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

int execute(char **input, t_data *data)
{
	int i = 0;
	data->is_pipe = 0;
	int start = 1;
	if (!input || !*input)
		return (0);
	while(input[i])
	{
		data->stdin = dup(0);
		data->stdout = dup(1);
		if(ft_strcmp(input[i], "(") == 0)
			data->is_subshell = 1;
		if(ft_strcmp(input[i], ")") == 0)
			data->is_subshell = 0;
		// start
		if(start == 1 && what_im(input[i]) == 0 && pipe_is_after(input, i) == 0)
			data->lastret = cmd_exec(data, input[i]);
		// start but pipe after
		// no '|' behind cmd and '|' after
		else if(data->is_pipe == 1  && what_before(input, i) == 3 && what_im(input[i]) == 0 && pipe_is_after(input, i) == 0)
		{
			data->is_pipe = 0;
			data->lastret = last_pipe(data,input[i]);
		}
		else if(data->is_pipe == 1 || (start == 1 && what_im(input[i]) == 0 && pipe_is_after(input, i) == 1)|| (what_before(input, i) == 1 && data->lastret == 0 && what_im(input[i]) == 0 && (pipe_is_after(input, i) == 1 || (what_before(input, i) == 3 && pipe_is_after(input, i) == 1)))
			|| (what_before(input, i) == 2 && data->lastret != 0 && what_im(input[i]) == 0 && (pipe_is_after(input, i) == 1 || (what_before(input, i) == 3 && pipe_is_after(input, i) == 1))))
		{
			data->is_pipe = 1;
			data->lastret = mid_pipe(data, input[i]);
		}
		// '&&' behind cmd
		else if(start == 0 && what_before(input, i) == 1 && what_im(input[i]) == 0 && data->lastret == 0)
			data->lastret = cmd_exec(data, input[i]);
		// '||' behind cmd
		else if(start == 0 && what_before(input, i) == 2 && what_im(input[i]) == 0 && data->lastret != 0)
			data->lastret = cmd_exec(data, input[i]);
		// '|' behind cmd and no '|' after
		// '|' behind cmd and '|' after
		else if(data->is_pipe == 1 && what_im(input[i]) == 0 && pipe_is_after(input, i) == 1)
			data->lastret = mid_pipe(data, input[i]);
		// '||' behind the parentheses cmd
		// '&&' behind the parentheses cmd
		else if((what_before(input, i) == 2 && what_im(input[i]) == 0 && data->lastret != 0 && ft_strcmp(input[i - 1], "(") == 0) || (what_before(input, i) == 1 && what_im(input[i]) == 0 && data->lastret == 0 && ft_strcmp(input[i - 1], "(") == 0))
			data->lastret = cmd_exec(data, input[i]);


		// printf("---> %d\n", data->lastret);
		i++;
		start = 0;
	}
	return data->lastret ;
}
