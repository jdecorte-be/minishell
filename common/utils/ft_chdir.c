/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:45:53 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/25 15:39:54 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_gethome(void)
{
	char	path[PATH_MAX];
	char	*str;
	size_t	i;
	size_t	trig;
	char	*home;

	str = getcwd(path, PATH_MAX);
	i = 0;
	trig = 0;
	while (str[i])
	{
		if (trig == 3)
		{
			break ;
		}
		if (str[i] && str[i] == '/')
		{
			trig++;
		}
		if (str[i])
			i++;
	}
	home = ft_substr(str, 0, i - 1);
	return (home);
}

char	*ft_getpwd(char c)
{
	char	*str;
	size_t	i;

	i = 0;
	if (ft_strchr("0+", c))
	{
		return (getenv("PWD"));
	}
	else if (c == '-')
	{
		str = getenv("OLDPWD");
		if (str == 0)
			str = "~-";
		return (str);
	}
	return (0);
}

void	ft_chdir_2(char *line, t_tmp *tmp, char *home, int e)
{
	char	*pwd;

	if (e == 1)
	{
		tmp->start = tmp->end;
		tmp->str = ft_strjoin1(tmp->str, home);
	}
	else if (e == 2)
	{
		if (tmp->end != tmp->start)
			tmp->str = ft_strjoin3(tmp->str,
					ft_substr(line, tmp->start, tmp->end - tmp->start));
	}
	else if (e == 3)
	{
		while (line[tmp->end] == '0')
			tmp->end++;
		if (ft_strchr("/ ", line[tmp->end]) || !line[tmp->end])
		{
			pwd = ft_getpwd(line[tmp->start + 1]);
			tmp->str = ft_strjoin1(tmp->str, pwd);
			tmp->start = tmp->end;
		}
	}
}

void	ft_chdir_3(char *line, t_tmp *tmp, char *home)
{
	tmp->start = tmp->end;
	if (((tmp->end && line[tmp->end - 1] == ' ') || !tmp->end) && line[tmp->end]
		&& line[tmp->end] == '~' && line[tmp->end + 1]
		&& ((line[tmp->end + 2] && ft_strchr(" /0", line[tmp->end + 2]))
			|| !line[tmp->end + 2]) && ft_strchr("+-0", line[tmp->end + 1]))
	{
		tmp->start = tmp->end++;
		if (ft_strchr("+-", line[tmp->end]))
			tmp->end++;
		ft_chdir_2(line, tmp, home, 3);
	}
	else if (line[tmp->end] && ft_strchr("\'\"", line[tmp->end]))
		ft_creat_tab2(line, &tmp->end, 0, 1);
	else if (((tmp->end && line[tmp->end - 1] == ' ') || !tmp->end)
		&& line[tmp->end] && ((ft_strchr(" /", line[tmp->end + 1])
				&& line[tmp->end + 1]) || !line[tmp->end + 1])
		&& line[tmp->end] == '~' && ++tmp->end)
		ft_chdir_2(line, tmp, home, 1);
	else if (line[tmp->end])
		tmp->end++;
	ft_chdir_2(line, tmp, home, 2);
}

char	*ft_chdir(char *line)
{
	t_tmp	tmp;
	char	*home;

	home = ft_gethome();
	tmp.end = 0;
	tmp.str = 0;
	while (line[tmp.end])
		ft_chdir_3(line, &tmp, home);
	free(home);
	free(line);
	return (tmp.str);
}
