#include "../../inc/minishell.h"

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

int execute(t_token *token)
{
	data->is_pipe = 0;
	int start = 1;
	t_token *tmp = token;

	while(tmp)
	{
		data->stdin = dup(0);
        data->stdout = dup(1);

		if(tmp->redirect.infd != 0)
			dup2(tmp->redirect.infd, 0);
		if(tmp->redirect.outfd != 0)
			dup2(tmp->redirect.outfd, 1);


		// start
		if(start == 1 && what_im(tmp->cmd) == 0)
			data->lastret = exec(tmp->cmd);
		else if(start == 0 && what_im(tmp->cmd) == 1)
		{
			if(data->lastret == 0 && tmp->next)
			{
				tmp = tmp->next;
				data->lastret = exec(tmp->cmd);
			}
		}
		else if(start == 0 && what_im(tmp->cmd) == 2)
		{
			if(data->lastret != 0 && tmp->next)
			{
				tmp = tmp->next;
				data->lastret = exec(tmp->cmd);
			}
		}
		dup2(data->stdin, 0);
		dup2(data->stdout, 1);
		tmp = tmp->next;
		start = 0;
	}
	return data->lastret ;
}
