#include "../../inc/minishell.h"

void redirect(t_token *token, int *savein, int *saveout)
{
	if(token->redirect.outfd != 0)
	{
		*savein = dup(0);
		dup2(token->redirect.infd, 0);
		// data->stdin_reset = dup(0);

	}
	if(token->redirect.outfd != 1)
	{
		*saveout = dup(1);
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

int exec_pipe(t_token *tmp)
{
	int ret = 0;

	while(data->is_pipe)
	{
		if(data->is_pipe == 1 && tmp->next && what_im(tmp->next->cmd) == 3)
			ret = pipex(tmp->cmd);
		else if (data->is_pipe == 1 && what_im(tmp->cmd) == 0)
		{
			data->is_pipe = 0;
			ret = exec(tmp->cmd);
			dup2(data->stdin_reset, 0);
			dup2(data->stdin_reset, 1);
		}
		tmp = tmp->next;
	}
	return ret;
}


int execute(t_token *token)
{
	data->is_pipe = 0;
	int start = 1;
	t_token *tmp = token;
	int is_and = 0;
	int is_or = 0;
	int is_ope = 1;
	int ret = 0;

	while(tmp)
	{
		// * touche pas
		tmp->cmd = ft_add_q_dollar(tmp->cmd);
		tmp->cmd = ft_chdollar(tmp->cmd);
		ft_redirect_for_john(tmp);
		tmp->cmd = ft_cut_chevron(tmp->cmd);
		tmp->cmd = ft_chwc(tmp->cmd);

		// * test
		printf("%d\n",token->redirect.infd);
		printf("%d\n",token->redirect.outfd);


		// * if is a cmd
		if(what_im(tmp->cmd) == 0)
		{
			if(is_and == 1 && ret == 0)
			{
				is_and = 0;
				if(data->is_pipe == 0 && tmp->next && what_im(tmp->next->cmd) == 3 && token->redirect.outfd == 1)
				{
					data->stdin_reset = dup(0);
					data->stdout_reset = dup(1);
					data->is_pipe = 1;
					ret = exec_pipe(tmp);
				}
				else
				{
					redirect(tmp, &data->stdin_reset, &data->stdout_reset);
					ret = exec(tmp->cmd);
				}
			}

			else if(is_or == 1 && ret != 0)
			{
				is_or = 0;
				if(data->is_pipe == 0 && tmp->next && what_im(tmp->next->cmd) == 3 && token->redirect.outfd == 1)
				{
					data->stdin_reset = dup(0);
					data->stdout_reset = dup(1);
					data->is_pipe = 1;
					ret = exec_pipe(tmp);
				}
				else
				{
					redirect(tmp, &data->stdin_reset, &data->stdout_reset);
					ret = exec(tmp->cmd);
				}
			}
			else if(start == 1 && data->is_pipe == 0 && tmp->next && what_im(tmp->next->cmd) == 3 && token->redirect.outfd == 1)
			{
				data->stdin_reset = dup(0);
				data->stdout_reset = dup(1);
				data->is_pipe = 1;
				ret = exec_pipe(tmp);
			}
			else if(start == 1)
			{
				redirect(tmp, &data->stdin_reset, &data->stdout_reset);
				ret = exec(tmp->cmd);
			}


			// * reset redir
			if(tmp->redirect.infd != 0 && data->is_pipe == 0)
				dup2(data->stdin_reset, 0);
			if(tmp->redirect.outfd != 1 && data->is_pipe == 0)
				dup2(data->stdout_reset, 1);
		}
		else
		{
			if(start == 0 && what_im(tmp->cmd) == 1)
				is_and = 1;
			else if(start == 0 && what_im(tmp->cmd) == 2)
				is_or = 1;
		}
		tmp = tmp->next;
		start = 0;
	}
	return ret ;
}
