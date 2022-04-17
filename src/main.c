#include "../inc/minishell.h"


void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
    if (tab)
	{
        while (tab[i])
        {
            free(tab[i]);
            i++;
        }
        free(tab);
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

void sigint_handler(int signum) { //Handler for SIGINT
   //Reset handler to catch SIGINT next time.
   (void)(signum);
    printf("\n ➜ 42-minishell ");
}

int	main(int ac, char **av, char **env)
{

    t_env   *d_env = malloc(sizeof(t_env));
	t_data	*data = malloc(sizeof(t_data));

	t_data	data;

	char	*line;

	data->isprio = 0;
	data->prioret = 10000;
    data->lastret = 0;
    d_env->env = env;
    d_env->exp = env;
    d_env->l_env = list_env(env);
    d_env->l_exp = list_env(env);



// testing =================================================
    if(ft_strcmp(av[1], "-c") == 0)
    {
        line = ft_strdup(av[2]);
        line = ft_epur_str(ft_pgross_str(line));
        // printf("%s\n", line);
        tokenize(line);
        char **res = ft_split(line, "\1");
        execute(res, data, d_env);

        ft_free_tab(res);
		free(line);
        return 0;

    }


// ==================================






    if(ac != 1)
        puterror("\e[0;37mUse : ./minishell without arguments\n");
	while (1)
	{
        printf("\e[0;36m ➜ ");
		line = readline(formpath());
        signal(SIGINT, sigint_handler);
        if (!line)
        {
            write(1, "\b\bexit\n", 7);
            exit (0);
        }
        if(*line)
            add_history(line);
    
        line = ft_epur_str(ft_pgross_str(line));
        tokenize(line);
        char **res = ft_split(line, "\1");
        execute(res, data, d_env);

        ft_free_tab(res);
		free(line);
	}
}
