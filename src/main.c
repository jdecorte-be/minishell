/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:16:34 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/04 19:16:30 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shlvlhandler(void)
{
	char	*var;
	int		shlvl;
	char	*join;
	char	*join2;
	char	*lvl;

	var = my_getenv("SHLVL", NULL);
	shlvl = ft_atoi(var) + 1;
	join = ft_strdup("_=/usr/bin/env");
	my_setenv(join);
	my_setenv("OLDPWD");
	if (shlvl > 1000)
		shlvl = 1;
	if (shlvl == 1000)
		my_setenv("SHLV");
	else
	{
		lvl = ft_itoa(shlvl);
		join2 = ft_strjoin("SHLVL=", lvl);
		my_setenv(join2);
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

void	initiate_values(t_data *g_data, char **env)
{
	g_data->lastret = 0;
	g_data->env = env;
	g_data->hd = 0;
	shlvlhandler();
	tcgetattr(0, &g_data->old);
	tcgetattr(0, &g_data->new);
	g_data->new.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &g_data->new);
	signal(SIGINT, c_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	main_2(void)
{
	char	*line;
	char	*pt;
	t_token	*token;

	while (1)
	{
		g_data->hd_stop = 0;
		pt = prompt();
		line = readline(pt);
		free(pt);
		if (*line)
			add_history(line);
		if (!line)
		{
			ft_putstr_fd("\b\bexit\n", 2);
			ft_exit(0);
		}
		if (ft_isprohibited(line) == 1)
		{
			free(line);
			continue ;
		}
		if (!*line)
			continue ;
		line = ft_epur_str(ft_chdir(ft_pgross_str((line))));
		token = ft_parsing(line);
		if (ft_token_error(token))
			continue ;
		free(line);
		execute(token);
		ft_tokenclean_all(&token);
	}
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	if (ac != 1)
	{
		puterror("\e[0;37mUse", "./minishell without arguments");
		return (0);
	}
	g_data = malloc(sizeof(t_data));
	if (!(g_data))
		return (0);
	initiate_values(g_data, env);
	main_2();
	ft_exit(g_data->lastret);
}
