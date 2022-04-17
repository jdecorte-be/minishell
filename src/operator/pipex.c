#include "../../inc/minishell.h"

void exec(char *cmd, char **env)
{
	int i;
	char **s_args = ft_split(cmd, " ");
	char **s_env = ft_split(getenv("PATH"), ":");
	char *execs;

	i = -1;
	while (s_env[++i])
	{
		s_env[i] = ft_strjoin(s_env[i], "/");
		execs = ft_strjoin(s_env[i], s_args[0]);
		free(s_env[i]);
		if (access(execs, X_OK) == 0)
			break ;
		free(execs);
	}
	execve(execs, &s_args[0], env);
	puterror(cmd);
}

int	pipex(t_env *data, char *cmd)
{
	pid_t	pid;
	int fd[2];

	pipe(fd);
	pid = fork();
	if (pid < 0)
		return -1;
	// first
	if (!pid)
	{
		dup2(fd[0], 0);
		dup2(data->infd[0], 1);
		close(fd[1]);
		close(data->outfd[0]);
		waitpid(pid, NULL, 0);
	}
	// second
	else
	{
		dup2(data->infd[0], 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(data->infd[0]);
		exec(cmd, data->env);
	}
	return 0;
}