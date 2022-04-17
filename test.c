#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include "./inc/minishell.h"
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
    int fd2;
	int fd1;
	char *tab[2];
	char tab2[2];
	int	fd[2];
	int	pfd[2];
	pid_t pid;
	char	*str;

	fd2 = open("a", O_RDWR);
	pipe(fd);
	pipe(pfd);
	tab[0] = "cat";
	tab[1] = 0;
	pid = fork();
	write(fd[1], "caca\n\0", 6);
	close(fd[1]);
	if (!pid)
	{
		dup2(fd2, 1);
		dup2(fd[0], 0);
		// close(fd[0]);
		execve("/bin/cat", tab, envp);
	}
	// close(pfd[1]);
	// close(fd[0]);
	// dup2(pfd[0], 0);
	// execve("/bin/cat", tab, envp);
	
    
}