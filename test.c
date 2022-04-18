#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include "./inc/minishell.h"
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
	printf("%s\n", ft_ecrase_q(argv[1]));
    
}