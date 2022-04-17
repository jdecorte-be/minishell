#include "../../inc/minishell.h"
#include <errno.h>

char *get_path(char *cmd)
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
	return exec;
}

int	pipex(t_env *d_env, char *cmd, int *p_fd)
{

	pid_t	pid;
	int 	err = 0;
	char	**args = ft_split(cmd, " ");

	pid = fork();
	if (pid < 0)
		return errno;
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		err = execve(get_path(cmd), &args[0], d_env->env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		waitpid(pid, NULL, 0);

	}
	close(p_fd[1]);
	close(p_fd[0]);
	return err;
}

int run_cmd(t_env *d_env, char *cmd)
{
	pid_t	pid;
	int err = 0;
	char **args = ft_split(cmd, " ");

	pid = fork();
	if (pid < 0)
		return errno;
	if (!pid)
	{
		if((err = execve(get_path(cmd), &args[0], d_env->env)) == -1)
		{
			printf("minishell: %s: command not found\n", cmd);
			exit (127);
		}
	}
	wait(&pid);
	return err;
}

int	pipe_handler(t_env *d_env, char **input)
{
	int		p_fd[2];
	int i = 0;
	int stdin = dup(0);
	int stdout = dup(1);
	pipe(p_fd);
	
	while(input[i + 1])
			pipex(d_env, input[i++], p_fd);
	run_cmd(d_env, input[i]);
	dup2(stdin, 0);
	dup2(stdout, 0);
	// puterror("$RES_REAL: ambiguous redirect\n");
	// printf("%d: %s\n", errno, input[i]);
	return 0;
}