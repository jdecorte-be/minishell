#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include "./inc/minishell.h"

int		main(int argc, char ** argv)
{
	ft_redirect(argv[1]);
}