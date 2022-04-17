#include "../../inc/minishell.h"

t_list	*ft_wcsearch(char *line)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	c;
	char	c1;
	t_list	*wc;

	i = 0;
	end = 0;
	wc = 0;
	while (line[end])
	{
		c1 = 0;
		start = end;
		if (line[end] && ft_strchr("\"\'", line[end]))
			ft_creat_tab2(line, &end, 0, 1);
		if (!ft_isspace(line[end]) && !ft_strchr("\'\"&|", line[end]))
		{
			while (line[end] && !ft_isspace(line[end]))
			{
				if (line[end++] == '*')
				{
					printf("1\n");
					c1 = 1;
				}
				printf("%c\n", line[end]);
			}
			printf("%zu\n%zu\n", start, end);
			if (c1 == 1)
			{
				printf("2\n");
				ft_lstadd_back(&wc, ft_lstnew(ft_substr(line, start, end - start)));
			}
		}
		else
			end++;
	}
	return (wc);
}





// t_list	*ft_wcfile(t_list *wc)
// {
// 	struct dirent	*dir;	
// 	DIR				*loc;
// 	char			path[PATH_MAX];
// 	t_list			*file;

// 	if (!wc)
// 		return (0);
// 	loc = opendir(getcwd(path, PATH_MAX));
// 	if (loc == 0)
// 		ft_error(5);
// 	dir = readdir(loc);
// 	while (dir)
// 	{
// 		printf("%s\n", dir->d_name);
// 		ft_lstadd_back(&file, ft_lstnew(dir->d_name));
// 		dir = readdir(loc);
// 	}
// 	if (closedir(loc) == -1)
// 		ft_error(6);
// }