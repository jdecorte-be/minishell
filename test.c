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
	char *tab[3];
	char *tab2[3];
	int	fd[2];
	int	pfd[2];
	pid_t pid;
	char	*str;

	fd1 = open("a", O_RDWR | O_TRUNC);
	fd2 = open("a", O_RDWR | O_TRUNC);
	// pipe(fd);
	// pipe(pfd);
	tab[0] = "echo";
	tab[1] = "123456789";
	tab[2] = 0;
	tab2[0] = "echo";
	tab2[1] = "9";
	tab2[2] = 0;
	pid = fork();
	// write(fd[1], "caca\n\0", 6);
	close(fd[1]);
	if (!pid)
	{
		dup2(fd1, 1);
		// dup2(fd[0], 0);
		// close(fd[0]);
		execve("/bin/echo", tab, envp);
	}
	waitpid(pid, 0, 0);
	// close(pfd[1]);
	// close(fd[0]);
	dup2(fd2, 1);
	execve("/bin/echo", tab2, envp);
	
    
}