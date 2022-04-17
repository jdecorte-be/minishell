#include "../../inc/minishell.h"

int	ft_free(char *line)
{
	free(line);
	return (1);
}

int	ft_str_isspace(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	ft_exist(char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (str[i] && i < len)
		i++;
	if (i == len)
		return (1);
	return (0);
}

char	*ft_lstmerge(t_list *lst)
{
	char	*str;

	if (!lst)
		return (0);
	str = 0;
	while (lst)
	{
		if (lst->next)
			str = ft_trijoin(str, lst->content, " ");
		else
			str = ft_strjoin(str, lst->content);
		lst = lst->next;
	}
	return (str);
}

char	*ft_woquote(char *line)
{
	char	*str;
	size_t	i;
	char	c;

	if (ft_strchr(line, '\'') || ft_strchr(line, '\"'))
	{
		str = malloc(sizeof(char) * (ft_strlen(line) - 2 + 1));
		i = 0;
		while (*line)
		{
			if (ft_strchr("\'\"", *line))
			{
				c = *line++;
				while (*line && *line != c)
					str[i++] = *line++;
				line++;
			}
			else
				str[i++] = *line++;
		}
	}
	else
		return (line);
	return (str);
}

// char	*ft_woquote(char *line)
// {
// 	char	*str;
// 	size_t	i;
// 	char	c;
// 	char	**tab;

// 	if (ft_strchr(line, '\'') || ft_strchr(line, '\"'))
// 	{
// 		i = 0;
// 		str = 0;
// 		tab = ft_split4(line, "*");
// 		while (tab[i])
// 			printf("tab = %s\n", tab[i++]);
// 		i =
// 		while (tab[i])
// 		{
// 			if (*line == '\'')
// 				tab[i] = ft_strtrim(tab[i], "\'");
// 			else if (*line == '\"')
// 				tab[i] = ft_strtrim(tab[i], "\'");
// 			i++;
// 		}
// 		i = 0;
// 		while (tab[i])
// 		{
// 			str = ft_strjoin(str, tab[i]);
// 			i++;
// 		}
// 	}
// 	else
// 		return (line);
// 	printf("str = %s\n", str);
// 	return (str);
// }