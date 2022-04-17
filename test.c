#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include "./inc/minishell.h"
#include <fcntl.h>

int		main(int argc, char ** argv, char **envp)
{
	write(100, "caca", 4);
}