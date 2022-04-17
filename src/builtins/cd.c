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
	// if(cmd[1][0] == '~');

	if(chdir(cmd[1]) == -1) return -1;
	return 0;
}