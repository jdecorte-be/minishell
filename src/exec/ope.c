#include "../../inc/minishell.h"

void redirect(t_token *token, int savein, int saveout)
{
	if(token->redirect.outfd != 0)
	{
		savein = dup(0);
		dup2(token->redirect.infd, 0);
		// data->stdin_reset = dup(0);

	}
	if(token->redirect.outfd != 1)
	{
		saveout = dup(1);
		dup2(token->redirect.outfd, 1);
		// data->stdout_reset = dup(1);
	}
}

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

int execute(t_token *token)
{
	data->is_pipe = 0;
	int start = 1;
	t_token *tmp = token;
	int		savein;
	int		saveout;
	int is_and = 0;
	int is_or = 0;
	int is_ope = 1;

	while(tmp)
	{
		tmp->cmd = ft_chdollar(tmp->cmd);


		ft_redirect_for_john(tmp);
		redirect(tmp, savein, saveout);
		tmp->cmd = ft_cut_chevron(tmp->cmd);




		// start
		if(start == 0 && what_im(tmp->cmd) == 1 && data->lastret == 0 || is_and == 1)
		{
			if(is_and == 1)
			{
				data->lastret = exec(tmp->cmd);
				is_and = 0;
			}
			is_and = 1;
		}
		
		else if(start == 0 && what_im(tmp->cmd) == 2 && data->lastret != 0 || is_or == 1)
		{
				if(is_or == 1)
				{
					data->lastret = exec(tmp->cmd);
					is_or = 0;
				}
				is_or = 1;
		}
		else if(data->is_pipe == 0 && what_im(tmp->cmd) == 0 && tmp->next && what_im(tmp->next->cmd) == 3 && token->redirect.outfd == 1)
		{
			data->stdin_reset = dup(0);
			data->stdout_reset = dup(1);
			data->is_pipe = 1;
			data->lastret = pipex(tmp->cmd);
		}
		else if(data->is_pipe == 1 && what_im(tmp->cmd) == 0 && tmp->next && what_im(tmp->next->cmd) == 3)
			data->lastret = pipex(tmp->cmd);
		else if (data->is_pipe == 1 && what_im(tmp->cmd) == 0)
		{
			data->is_pipe = 0;
			data->lastret = exec(tmp->cmd);
			dup2(data->stdin_reset, 0);
			dup2(data->stdin_reset, 1);
		}
		else if(start == 1 && what_im(tmp->cmd) == 0 && data->is_pipe == 0)
			data->lastret = exec(tmp->cmd);


		if(token->redirect.infd != 0 && data->is_pipe == 0)
			dup2(savein, 0);
		if(token->redirect.outfd != 1 && data->is_pipe == 0)
			dup2(saveout, 1);
		// printf("%s --> %d %d \n", tmp->cmd,tmp->redirect.infd, tmp->redirect.outfd);

		tmp = tmp->next;
		start = 0;
		// printf("-----> %d\n", data->lastret);
	}
	return data->lastret ;
}
