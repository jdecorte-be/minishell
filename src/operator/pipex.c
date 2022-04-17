#include "../../inc/minishell.h"
#include <errno.h>


void exec(char *cmd, char **env)
{
	int i;
	char **s_env = ft_split(getenv("PATH"), ":");
	char *execs;

	i = -1;

	char **s_cmd = ft_split(cmd, " ");

	if (access(s_cmd[0], X_OK) == 0)
		execs = s_cmd[0];
	else
	{
		while (s_env[++i])
		{
			s_env[i] = ft_strjoin(s_env[i], "/");
			execs = ft_strjoin(s_env[i], s_cmd[0]);
			free(s_env[i]);
			if (access(execs, F_OK | X_OK) == 0)
				break ;
			free(execs);
		}
	}
	if (execve(execs, &s_cmd[0], env) == -1)
	{
		printf("minishell: %s: command not found\n", cmd);
		exit (127);
	}
	
}

int	pipex(t_env *data, char *cmd)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid < 0)
		return -1;
	// first
	if (pid)
		waitpid(pid, NULL, 0);
	// second
	else
		exec(cmd, data->env);
	// printf("= %d = \n", errno);
	return errno;
}