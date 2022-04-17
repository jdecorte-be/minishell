#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include "./inc/minishell.h"
#include <fcntl.h>

int		main(int argc, char ** argv, char **envp)
{
	int fd[2];

	fd[0] = open("b", O_RDWR | O_TRUNC);
	printf("%d\n", fd[0]);
	fd[1] = dup(1);
	dup2(fd[0], 1);
	write(1, "bonjour", 7);
	dup2(fd[1], 1);
	write(1, "salut", 5);
}