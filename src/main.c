#include "../inc/minishell.h"

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
    return res;
}

int	main(int ac, char **av, char **env)
{
    (void)av;
    
    t_env   *d_env = malloc(sizeof(t_env));
	t_data	*data = malloc(sizeof(t_data));
	char	*line;

	// char	**tab;
	data = 0;

    d_env->env = env;
    d_env->exp = env;
    d_env->l_env = list_env(env);
    d_env->l_exp = list_env(env);
// testing
    // if(ft_strcmp(av[1], "-c") == 0)
    // {
    //     line = av[2];
    //     char **s_line = ft_split(line, " ");
    //     int i = 0;
    //     while(s_line[i + 1])
    //         i++;
    //     int j = 0;
    //     while(s_line[i][j])
    //     {
    //         if(s_line[i][j] == '\n')
    //             s_line[i][j] = '\0';
    //         j++;
    //     }
    //     cmdlexer(s_line, d_env);
    //     return 0;
    // }
// ===================
    if(ac != 1)
        puterror("\e[0;37mUse : ./minishell without arguments\n");
	while (1)
	{
        printf("➜ ");
		line = readline(formpath());
        char **s_line = ft_split(line, " ");
        data->lastret = cmdlexer(s_line, d_env);
        printf("%d\n", data->lastret);
		free(line);
	}
	// int i = 0;
	// tab = ft_split2(line, "\t\f\r\v\n ");
	// while(tab[i])
	// {
	// 	printf("|%s|\n", tab[i]);
	// 	i++;
	// }
	// printf("")
}
