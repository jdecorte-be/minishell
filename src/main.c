#include "../inc/minishell.h"
#include <errno.h>

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
    char *sub;

    path = getcwd(path, 1024);
    int i = ft_strlen(path);
    while(path[--i] != '/');
    sub = ft_substr(path, i + 1, ft_strlen(path));
    line = ft_strjoin(sub," ❯ ");
    free(sub);
    return line;
}


void	test(t_data *data)
{
	tcgetattr(0, &data->old);
	tcgetattr(0, &data->new);
	data->new.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &data->new);
}

int	main(int ac, char **av, char **env)
{
    (void)av;
	char	*line;


    if(ac != 1)
        puterror("\e[0;37mUse", "./minishell without arguments");
    data = malloc(sizeof(t_data));
	if(!(data))
        return 0;
	test(data);
    data->lastret = 0;
    data->env = env;
    data->hd = 0;
    shlvlhandler();
	signal(SIGINT, c_handler);
	signal(SIGQUIT, SIG_IGN);
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
      	execute(token);


    }
	tcsetattr(0, TCSANOW, &data->new);
    exit(data->lastret);
    free(data->env);
    free(data);
}
