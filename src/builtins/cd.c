#include "builtins.h"

// work sauf avec unset et les pipes
int pwd()
{
	char buffer[1024];

	if(getcwd(buffer, sizeof(buffer)) == NULL)
		return -1;
	printf("%s\n", buffer);
	return 0;
}

int cd(char **cmd)
{
	char *togo = NULL;
	// if(cmd[1][0] == '~');
	if(!cmd[1])
		return 134;
	if(cmd[1][0] == '~')
		togo = ft_strjoin(getenv("HOME"),ft_substr(cmd[1], 1, ft_strlen(cmd[1]) - 1));
	else
		togo = cmd[1];
	if(chdir(togo) == -1)
		return -1;
	return 0;
}