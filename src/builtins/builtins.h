#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct l_env
{
    char **env;
    t_list *l_env;
    char **exp;
    t_list *l_exp;
}   t_env;

int checkvalid(char *cmd);
char	*my_getenv(char *tochr, t_list *lst);
int     echo(char **args);
int     pwd();
int     cd(char **args);
int     export(char **cmd,t_env *data);
int     unset(char **cmd, t_env *data);
int     printList(t_list *head);

t_list  *list_env(char **env);
char    **listtotab(t_list *lst);
void    env_cmd(t_env *data);
void	*ft_memdel(void *ptr);
void replace_env(char *cmd, t_list *env);

#endif // BUILTINS_H