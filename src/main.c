#include "../inc/minishell.h"
#include <errno.h>


void printlist(t_token *token)
{
    int i = 0;
    while(token)
    {
        printf("%s\n", token->cmd);
        printf("%d\n", token->redirect.infd);
        printf("%d\n", token->redirect.outfd);
        printf("================================================================\n");
    // if (token->sub_token)
    //     token = token->sub_token;
    // else if (token->next)
    //     token = token->next;
    // else if (!token->next && token->sup_token)
    //     token = token->sup_token->next;
    // else
        token = token->next;
    }
}


// void	newprompt(int sig)
// {
//     printf("\n");
//     rl_on_new_line();
//     rl_replace_line("", 0);
//     rl_redisplay();
// }

void shlvlhandler()
{
    char *var = getenv("SHLVL");
    if(var)
    {
        int shlvl = ft_atoi(var) + 1;
        my_setenv(ft_strjoin("SHLVL", ft_itoa(shlvl)));
    }
}

char *prompt()
{
    char    *path = NULL;
    char    *line;

    ft_putstr_fd("\e[0;36m", 1);
    path = getcwd(path, 1024);
    int i = ft_strlen(path);
    while(path[--i] != '/');
    line = ft_strjoin(ft_substr(path, i + 1, ft_strlen(path)),"\e[0;37m ❯ ");
    return line;
}

int	main(int ac, char **av, char **env)
{
    (void)av;
	char	*line;
    unsetenv("OLDPWD");
    if(!(data = malloc(sizeof(t_data))))
        return 0;
    data->lastret = 0;
    data->env = env;
    data->hd = 0;
    shlvlhandler();
    if(ac != 1)
        puterror("\e[0;37mUse", "./minishell without arguments");
    while (1)
    {
        // signal(SIGINT, newprompt);
        line = readline(prompt());
        if (!line)
        {
            ft_putstr_fd("\b\bexit\n", 2);
            exit (0);
        }
        if(*line)
            add_history(line);
    
        line = ft_epur_str(ft_chwc(ft_chdir(ft_pgross_str((line)))));
        t_token *token = ft_parsing(line);
        printlist(token);
        // to delete
        execute(token);
    }
        // exit(ret);

}
