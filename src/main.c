#include "../inc/minishell.h"
#include <errno.h>

void shlvlhandler()
{
    char *var = my_getenv("SHLVL", NULL);
    int shlvl = ft_atoi(var) + 1;
    char *join = ft_strjoin("_=", "/usr/bin/env");
    char *join2;
    char *lvl;

    my_setenv(join, 1);
    my_setenv("OLDPWD", 1);
    if (shlvl > 1000)
        shlvl = 1;
    if (shlvl == 1000)
            my_setenv("SHLV", 1);
    else
    {
        lvl = ft_itoa(shlvl);
        join2 = ft_strjoin("SHLVL=", lvl);
        my_setenv(join2, 1);
    }
    free(lvl);
    free(join);
    free(join2);
}

char *prompt()
{
    char    *path = NULL;
    char    *line;
    char *sub;

    path = getcwd(path, 1024);
    int i = ft_strlen(path);
    while(path[--i] != '/');
    sub = ft_substr(path, i + 1, ft_strlen(path));
    line = ft_strjoin(sub," ❯ ");
    free(path);
    free(sub);
    return line;
}

int	main(int ac, char **av, char **env)
{
    (void)av;
	char	*line;
    char    *pt;

    if(ac != 1)
        puterror("\e[0;37mUse", "./minishell without arguments");
    if(!(data = malloc(sizeof(t_data))))
        return 0;
    data->lastret = 0;
    data->env = env;
    data->hd = 0;
    shlvlhandler();
    while (1)
    {
        pt = prompt();
        line = readline(pt);
        free(pt);
        if (ft_isprohibited(line) == 1)
            continue ;
        if (!line)
        {
            ft_putstr_fd("\b\bexit\n", 2);
            exit (0);
        }
        if(*line)
            add_history(line);
        line = ft_epur_str(ft_chdir(ft_pgross_str((line))));
        t_token *token = ft_parsing(line);
        execute(token);
    }
    free(data->env);
    free(data);
    my_setenv(NULL, 2);
}
