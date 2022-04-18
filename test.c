#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include "./inc/minishell.h"
#include <fcntl.h>
# include <stdio.h>
int main(int argc, char **argv, char **envp)
{
	printf("Delete: %s\n", *envp);
	ft_memmove(*envp, *envp + ft_strlen(*envp), ft_strlen(*envp) + 1);
	int i = 0;
	while(envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}