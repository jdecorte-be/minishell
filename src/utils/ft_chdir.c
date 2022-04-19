/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:45:53 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/12 19:04:06 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*ft_chdir(char *line)
{
	size_t	start;
	size_t	end;
	char	*home;
	char	*str;
	char	*pwd;

	home = ft_gethome();
	end = 0;
	str = 0;
	while (line[end])
	{
		start = end;
		if (((end && line[end - 1] == ' ') || !end) && line[end] && line[end]
			== '~' && line[end + 1] && ((line[end + 2] && ft_strchr(" /0",
						line[end + 2])) || !line[end + 2])
			&& ft_strchr("+-0", line[end + 1]))
		{
			start = end++;
			if (ft_strchr("+-", line[end]))
				end++;
			while (line[end] == '0')
				end++;
			if (ft_strchr("/ ", line[end]) || !line[end])
			{
				pwd = ft_getpwd(line[start + 1]);
				str = ft_strjoin1(str, pwd);
				start = end;
			}
		}
		else if (line[end] && ft_strchr("\'\"", line[end]))
			ft_creat_tab2(line, &end, 0, 1);
		else if (((end && line[end - 1] == ' ') || !end) && line[end]
			&& ((ft_strchr(" /", line[end + 1]) && line[end + 1])
				|| !line[end + 1]) && line[end] == '~' && ++end)
		{
			start = end;
			str = ft_strjoin1(str, home);
		}
		else if (line[end])
			end++;
		if (end != start)
			str = ft_strjoin3(str, ft_substr(line, start, end - start));
	}
	free(home);
	free(line);
	return (str);
}
