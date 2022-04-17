#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include "./inc/minishell.h"

int		main(int argc, char ** argv)
{
	printf("%s\n", ft_ecrase_q(argv[1]));
}