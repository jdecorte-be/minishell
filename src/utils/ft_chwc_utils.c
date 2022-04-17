#include "../../inc/minishell.h"

t_list	*ft_wcsearch(char *line)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	c;
	char	c1;

	i = 0;
	end = 0;
	while (line[end])
	{
		start = end;
		while (!ft_isspace(line[end]) && ft_strchr("\'\"&|", line[end]))
		{
			if (line[end] == '*')
		}
		// start = end;
		// if (line[start] != '*')
		// 	start++;
		// while (ft_strchr("\'\"", line[start]))
		// {
		// 	c = line[start++];
		// 	while (line[start] != c)
		// 		start++;
		// 	start++;
		// }
		// end = start;
	}
}





t_list	*ft_wcfile(t_list *wc)
{
	struct dirent	*dir;	
	DIR				*loc;
	char			path[PATH_MAX];
	t_list			*file;

	if (!wc)
		return (0);
	loc = opendir(getcwd(path, PATH_MAX));
	if (loc == 0)
		ft_error(5);
	dir = readdir(loc);
	while (dir)
	{
		printf("%s\n", dir->d_name);
		ft_lstadd_back(&file, ft_lstnew(dir->d_name));
		dir = readdir(loc);
	}
	if (closedir(loc) == -1)
		ft_error(6);
}