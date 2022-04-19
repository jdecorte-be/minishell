/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:16:34 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 18:28:34 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	shlvlhandler(void)
{
	char	*var;
	int		shlvl;
	char	*join;
	char	*join2;
	char	*lvl;

	var = my_getenv("SHLVL", NULL);
	shlvl = ft_atoi(var) + 1;
	join = ft_strjoin("_=", "/usr/bin/env");
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

char	*prompt(void)
{
	char	*path;
	char	*line;
	char	*sub;
	int		i;

	path = NULL;
	path = getcwd(path, 1024);
	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	sub = ft_substr(path, i + 1, ft_strlen(path));
	line = ft_strjoin(sub, " ❯ ");
	free(path);
	free(sub);
	return (line);
}

void	test(t_data *data)
{
	tcgetattr(0, &g_data->old);
	tcgetattr(0, &g_data->new);
	g_data->new.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &g_data->new);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*pt;
	t_token	*token;

	(void) av;
	if (ac != 1)
		puterror("\e[0;37mUse", "./minishell without arguments");
	g_data = malloc(sizeof(t_data));
	if (!(g_data))
		return (0);
	test(g_data);
	g_data->lastret = 0;
	g_data->env = env;
	g_data->hd = 0;
	shlvlhandler();
	signal(SIGINT, c_handler);
	signal(SIGQUIT, SIG_IGN);
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
		if (*line)
			add_history(line);
		line = ft_epur_str(ft_chdir(ft_pgross_str((line))));
		token = ft_parsing(line);
		execute(token);
	}
	tcsetattr(0, TCSANOW, &g_data->new);
	exit(g_data->lastret);
	free(g_data->env);
	free(g_data);
	my_setenv(NULL, 2);
}
