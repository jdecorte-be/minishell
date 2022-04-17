#include "builtins.h"

// echo Hello World ! && echo '$path'
// marche + fix lors du parsing avec '' et ""
// code d'exit a modifier

// void delete_ext_quotes(char **args)

int echo(char **args)
{
	int i;

	i = 1;
    if(args[1])
    {
        while(ft_strncmp(args[i], "-n", 2) == 0)
            i++;
        while(args[i])
        {
            printf("%s", args[i]);
            if(args[i + 1])
                printf(" ");
            i++;
        }
        if(ft_strncmp(args[1], "-n", 2) != 0)
            printf("\n");
    }
    else
        printf("\n");
    return 0;
}