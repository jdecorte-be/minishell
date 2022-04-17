#include "../inc/minishell.h"
#include <errno.h>

void print2darray(char **arr)
{
    int i = 0;
    while(arr[i])
    {
        printf("%d\\ %s ", i ,arr[i]);
        i++; //
    }
}

void shlvlhandler(t_data *data)
{
    char *var = getenv("SHLVL");
    if(var)
    {
        int shlvl = ft_atoi(var) + 1;
        my_setenv("SHLVL", ft_itoa(shlvl), data);

    }
}

char **parsing(char *input)
{
	tokenize(ft_epur_str(ft_pgross_str(input)));
	char **res = ft_split(input , "\1");
    return res;
}

char *formpath()
{
    char path[1024];
    getcwd(path, sizeof(path));
    int i = ft_strlen(path);
    while(path[--i] != '/');
    char *res = malloc((ft_strlen(path) - i + 2) * sizeof(char));
    int j = 0;
    while(path[++i])
        res[j++] = path[i];
    res[j] = ' ';
    res[j + 1] = '\0';
    res = ft_strjoin(res, "\e[0;37m");
    return res;
}

void sigint_handler(int signum)
{
    (void)signum;

    ft_putstr_fd("\n\e[0;36m ➜ ", 1);
    ft_putstr_fd(formpath(), 1);
}


int	main(int ac, char **av, char **env)
{
    (void)av;
    int errno;
	t_data	*data;

    if(!(data = malloc(sizeof(t_data))))
        return 0;
    data->lastret = 0;
    data->env = env;
    free(my_getenv("OLDPWD", data));
    shlvlhandler(data);

	char	*line;
    int ret;


    if(ac != 1)
        puterror("\e[0;37mUse : ./minishell without arguments\n");
    while (1)
    {
        signal(SIGINT, sigint_handler);
        signal(SIGTSTP , sigint_handler);
        printf("\e[0;36m ➜ ");
        line = readline(formpath());
        if (!line)
        {
            ft_putstr_fd("\b\bexit\n", 2);
            exit (0);
        }
        if(line[0] != '\n')
            add_history(line);
    
        line = tokenize(ft_chdir(ft_chwc(ft_chdollar(ft_epur_str(ft_pgross_str(line))))));
        char **res = ft_split(line, "\1");

        // to delete
            // print2darray(res);
        ret = execute(res, data);
    }
        // exit(ret);

}
