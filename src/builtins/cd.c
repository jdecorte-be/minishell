# include "../../inc/minishell.h"


int pwd()
{
	char buffer[1024];

	if(!getcwd(buffer, sizeof(buffer)))
		return -1;
	printf("%s\n", buffer);
	exit(0);
}

int cd(char **cmd, t_data *d_env)
{
	char pwd_buff[1024];
	char oldpwd_buff[1024];

	if(!getcwd(oldpwd_buff , sizeof(oldpwd_buff)))
		return -1;
	if(!cmd[1])
		return 134;
	if(chdir(cmd[1]) == -1)
		perror("cd");
	else
	{
		if(!getcwd(pwd_buff , sizeof(pwd_buff)))
			return -1;
		my_setenv("PWD", pwd_buff, d_env);
		my_setenv("OLDPWD", oldpwd_buff, d_env);
	}
	exit(0);
}