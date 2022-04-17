#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>

typedef struct s_mini
{

}		t_mini;

void exec(char *cmd, char **env);
void	puterror(char *str);

#endif // MINISHELL_H