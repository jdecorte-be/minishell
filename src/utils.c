#include "minishell.h"

void	puterror(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
}

void exec(char *cmd, char **env)
{
	int i;
	char **s_args = ft_split(cmd, ' ');
	char **s_env = ft_split(getenv("PATH"), ':');
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
	exit(127);
}