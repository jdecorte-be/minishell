# include "../../inc/minishell.h"


int pwd()
{
	char buffer[1024];

	if(!getcwd(buffer, sizeof(buffer)))
		return -1;
	ft_putstr_fd(buffer, 1);
	return 0;
}

int cd(char **cmd)
{
	char pwd_buff[1024];

	if(!cmd[1])
		return 0;
	if(chdir(ft_ecrase_q(cmd[1])) == -1)
	{
		perror("cd");
		return 1;
	}
	else
	{
		if(!getcwd(pwd_buff , sizeof(pwd_buff)))
			return -1;
		char *PWD_var = my_getenv("PWD", NULL);
		if(PWD_var)
		{
			char *tmp =  my_getenv("PWD",NULL);
			my_setenv(ft_strjoin("OLDPWD=", tmp));
			my_setenv(ft_strjoin("PWD=", pwd_buff));
		}
	}
	return 0;
}