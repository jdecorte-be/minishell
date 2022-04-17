void exec(t_pipex *tab, char *cmd)
{
	int i;
	char **args = ft_split(cmd, ' ');

	i = -1;
	while (tab->allpath[++i])
	{
		tab->allpath[i] = ft_strjoin(tab->allpath[i], "/");
		tab->exec = ft_strjoin(tab->allpath[i], args[0]);
		free(tab->allpath[i]);
		if (access(tab->exec, X_OK) == 0)
			break ;
		free(tab->exec);
	}
	execve(tab->exec, &args[0], tab->env);
	puterror(cmd);
	puterror(": command not found\n");;
	exit(127);
}