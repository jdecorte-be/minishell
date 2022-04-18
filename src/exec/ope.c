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
	int is_and = 0;
	int is_or = 0;
	int start = 1;
	t_token *tmp = token;
	while(tmp)
	{

		data->inredirrs = tmp->redirect.infd;
		data->outredirrs = tmp->redirect.outfd;
		if(data->inredirrs != 0)
			data->stdin_reset = dup(0);
		if(data->outredirrs != 1)
			data->stdout_reset = dup(1);

		// start
		if(start == 0 && what_im(tmp->cmd) == 1)
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
		else if(data->is_pipe == 0 && what_im(tmp->cmd) == 0 && tmp->next && tmp->next->cmd[0] == '|')
		{
			data->stdin_reset = dup(0);
			data->stdout_reset = dup(1);
			data->is_pipe = 1;
			data->lastret = pipex(tmp->cmd);
		}
		else if(data->is_pipe == 1 && what_im(tmp->cmd) == 0 && tmp->next && tmp->next->cmd[0] == '|')
			data->lastret = pipex(tmp->cmd);
		else if (data->is_pipe == 1 && what_im(tmp->cmd) == 0)
		{
			data->is_pipe = 0;
			data->lastret = exec(tmp->cmd);
			dup2(data->stdin_reset, 0);
			dup2(data->stdout_reset, 1);
		}
		else if(start == 1 && what_im(tmp->cmd) == 0 && data->is_pipe == 0)
			data->lastret = exec(tmp->cmd);
		tmp = tmp->next;
		start = 0;
		// printf("-----> %d\n", data->lastret);
	}
	return data->lastret ;
}
