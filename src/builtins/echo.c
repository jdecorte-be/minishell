# include "../../inc/minishell.h"

int echo(char **args)
{
	int i;
    int option = 0;
	i = 1;
    if(args[1])
    {
        while(args[i][0] == '-' && args[i][1] == 'n')
        {
            option = 1;
            i++;
        }
        while(args[i])
        {

            printf("%s", args[i]);
            if(args[i + 1])
                printf(" ");
            i++;
        }
        if(option == 0)
            printf("\n");
    }
    else
        printf("\n");
    return 0;
}