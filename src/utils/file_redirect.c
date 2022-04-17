#include "../../inc/minishell.h"

char	*ft_chrredirect(char *line, char c)
{
	size_t	end;

	end = 0;
	if	(ft_strchr("<>", line[end]))
		end++;
	while (ft_isspace(line[end]))
		end++;
	while (line[end] && !ft_isspace(line[end]))
		end++;
	return (ft_substr(line, 0, end));
}

t_list	*ft_infile(char *line)
{
	t_list	*lst;
	size_t	i;
	char	*str;

	lst = 0;
	i = 0;
	while (line[i])
	{
		// if (*line && *(line + 1) && ft_strncmp(*line, ">>", 1))
		// if (*line && *(line + 1) && ft_strncmp(*line, "<<", 1))
		if (line[i] && ft_strchr("<", line[i]))
		{
			str = ft_chrredirect(line + i, '<');
			ft_lstadd_back(&lst, ft_lstnew(str));
			i += ft_strlen(str);
		}
		else
			i++;

	}
	return (lst);
}

void	ft_redirect(char *line)
{
	t_direct	file;

	if (!line)
		return (0);
	file.infile = ft_infile(line);
	printf("%s|\n", (char *)file.infile->content);
}