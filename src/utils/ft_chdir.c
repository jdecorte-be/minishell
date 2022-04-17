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
			printf("3\n");
			break ;
		}
		if (str[i] && str[i] == '/')
		{
			printf("1\n");
			trig++;
		}
		if (str[i])
		{
			printf("2\n");
			i++;
		}
	}
	home = ft_substr(str, 0, i - 1);
	return (home);
}

char	*ft_chdir(char *line)
{
	size_t	start;
	size_t	end;
	char	*home;
	char	*str;

	home = ft_gethome();
	end = 0;
	str = 0;
	while (line[end])
	{
		start = end;
		if (ft_strchr("\'\"", line[end]))
			ft_creat_tab2(line, &end, 0, 1);
		else if (line[end] == '~' && ++end)
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
