#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include "./inc/minishell.h"
#include <fcntl.h>

int		main(int argc, char ** argv, char **envp)
{
	int *fd;
	int	fd1;
	int fd2;

	fd = 0;
	// pipe(fd);
	// fd1 = fd[1];
	// fd2 = fd[0];
	// pipe(fd);
	printf("fd1 %d\nfd2 %d\nfd %p\n", fd1, fd2, fd);
}
