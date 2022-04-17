#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include "./inc/minishell.h"
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
    char    *tab[3];

    printf("%d\n", open(0, O_RDWR | O_CREAT));



    
}