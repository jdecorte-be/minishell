#include "../../inc/minishell.h"
#include <errno.h>


void exec(t_env *d_env, char *cmd)
{
	int i;
	char **args = ft_split(cmd, " ");
	char *exec;
	char **allpath = ft_split(getenv("PATH"), ":");
	i = -1;
	if (access(args[0], X_OK) == 0)
		exec = args[0];
	else
	{
		while (allpath[++i])
		{
			allpath[i] = ft_strjoin(allpath[i], "/");
			exec = ft_strjoin(allpath[i], args[0]);
			free(allpath[i]);
			if (access(exec, F_OK | X_OK) == 0)
				break ;
			free(exec);
		}
	}
	if(execve(exec, &args[0], d_env->env) == -1)
	{
		printf("minishell: %s: command not found\n", cmd);
		exit (127);
	}
}

int	pipex(t_env *d_env, char *cmd)
{
	pid_t	pid;
	int p_fd[2];


	pipe(p_fd);
	pid = fork();
	if (pid < 0)
		return errno;

	// first
	if (pid)
	{
		dup2(p_fd[0], 0);
		// dup2(fd2, 1);
		close(p_fd[1]);
		// close(fd2);
		waitpid(pid, NULL, 0);
	}
	// second
	else
	{
		// dup2(fd1, 0);
		dup2(p_fd[1], 1);
		close(p_fd[0]);
		// close(fd1);
		exec(d_env, cmd);
	}
	return errno;
}

int	pipe_handler(t_env *d_env, char **input)
{
	if (splitlen(input) >= 3)
	{
		int i = 0;
		while(input[i + 1] && ft_strcmp(input[i + 1],"&&") != 0 && ft_strcmp(input[i + 1],"||") != 0)
		{
			if(input[i][0] == '|')
				i++;
			else
				pipex(d_env, input[i++]);
			// i++;
		}
		exec(d_env, input[i]);
		// close(tab->fd1);
		// close(tab->fd2);
	}
	else
		puterror("$RES_REAL: ambiguous redirect\n");
	return errno;
}