#include "../inc/minishell.h"
#include <errno.h>

int syntax_check(t_token *token)
{
    t_token *tmp = token;
    int is_ope = 1;
    int start = 1;
    int old_ope;

    if(tmp == NULL)
        return 0;
    while(tmp)
    {
        old_ope = is_ope;
        if(what_im(tmp->cmd) == 0)
            is_ope = 0;
        else
            is_ope = 1;
        if((is_ope == old_ope )|| (start == 1 && is_ope == 1))
        {
            data->lastret = 2;
            puterror("syntax error near unexpected token", tmp->cmd);
            return 0;
        }
        start = 0;
        tmp = tmp->next;
    }
    return 1;
}

void shlvlhandler()
{
    char *var = my_getenv("SHLVL", NULL);
    int shlvl = ft_atoi(var) + 1;

    my_setenv(ft_strjoin("_=", "/usr/bin/env"));
    my_setenv("OLDPWD");
    if (shlvl > 1000)
        shlvl = 1;
    if (shlvl == 1000)
            my_setenv("SHLV");
    else
        my_setenv(ft_strjoin("SHLVL=", ft_itoa(shlvl)));
}

char *prompt()
{
    char    *path = NULL;
    char    *line;

    path = getcwd(path, 1024);
    int i = ft_strlen(path);
    while(path[--i] != '/');
    line = ft_strjoin(ft_substr(path, i + 1, ft_strlen(path))," ❯ ");
    return line;
}

int	main(int ac, char **av, char **env)
{
    (void)av;
	char	*line;

    if(!(data = malloc(sizeof(t_data))))
        return 0;
    data->lastret = 0;
    data->env = env;
    data->hd = 0;

    shlvlhandler();
   


    // * TESTER ===============================
    if (ac >= 3 && !ft_strncmp(av[1], "-c", 2))
    {
        char *tmp = ft_strdup(av[2]);
        line = ft_epur_str(ft_chdir(ft_pgross_str((tmp))));
        t_token *token = ft_parsing(line);
        if(syntax_check(token) == 0);
        else
            data->lastret = execute(token);
        exit(data->lastret);
    }




    if(ac != 1)
        puterror("\e[0;37mUse", "./minishell without arguments");
    while (1)
    {
        line = readline(prompt());
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
        if(syntax_check(token) == 0);
        else
            data->lastret = execute(token);


    }

}
