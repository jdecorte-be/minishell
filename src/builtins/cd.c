#include "builtins.h"



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
	if(!cmd[1])
		return 134;
	togo = cmd[1];
	if(chdir(togo) == -1)
	{
		perror("cd");
		exit(1);
	}
	return 0;
}