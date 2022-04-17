#include "../inc/minishell.h"
#include <errno.h>

// void print2darray(char **arr)
// {
//     int i = 0;
//     while(arr[i])
//     {
//         printf("%d\\ %s ", i ,arr[i]);
//         i++; //
//     }
// }

t_data	*data;

void shlvlhandler(t_data *data)
{
    char *var = getenv("SHLVL");
    if(var)
    {
        int shlvl = ft_atoi(var) + 1;
        my_setenv("SHLVL", ft_itoa(shlvl), data);

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

    if(!(data = malloc(sizeof(t_data))))
        return 0;
    data->lastret = 0;
    data->env = env;
    free(my_getenv("OLDPWD", data));
    shlvlhandler(data);

	char	*line;


    if(ac != 1)
        puterror("\e[0;37mUse : ./minishell without arguments\n");
    while (1)
    {
        signal(SIGINT, sig_handler);
        signal(SIGTSTP, sig_handler);
        line = readline(prompt());
        if (!line)
        {
            ft_putstr_fd("\b\bexit\n", 2);
            exit (0);
        }
        if(line[0] != '\n')
            add_history(line);
    
        line = ft_chdir(ft_chwc(ft_chdollar(ft_epur_str(ft_pgross_str(line)))));
        data->token = ft_parsing(line);
        // to delete
        // ret = execute(res, data);
        wait(NULL);
    }
        // exit(ret);


}
