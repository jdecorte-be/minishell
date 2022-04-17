#include "../../inc/minishell.h"

void	nothing(void)
{
}


char	*ft_chrredirect(char *line, char c)
{
	size_t	end;
	size_t	start;
	int		i;

	i = 2;
	end = 0;
	if (line[end] == '<')
		end++;
	else
		while (line[end] == '>' && i--)
			end++;
	if (ft_isspace(line[end]))
		while (ft_isspace(line[end]))
			end++;
	else

	start = end;
	while (line[end] && !ft_isspace(line[end]))
		end++;
	return (ft_substr(line, 0, end));//remplacer le 0 par start; et end par end - start;
}

t_list	*ft_file(char *line, char c)
{
	t_list	*lst;
	size_t	i;
	char	*str;

	lst = 0;
	i = 0;
	while (line[i])
	{
		// if (*line && *(line + 1) && ft_strncmp(*line, ">>", 1))
		// if (*line && *(line + 1) && ft_strncmp(line + i, "<<", 1))
		// 	i++;
		if (line[i] && line[i] == c && line[i + 1] && line[i + 1] != '<')
		{
			str = ft_chrredirect(line + i, c);
			ft_lstadd_back(&lst, ft_lstnew(str));
			i += ft_strlen(str);
		}
		else if (line[i] && line[i + 1] && line[i] == '<' && line[i + 1] == '<')
			i += 2;
		else
			i++;

	}
	return (lst);
}

t_redirect	ft_init_redirect(void)
{
	t_redirect	file;

	file.infile = 0;
	file.outfile = 0;
	file.infd = 0;
	file.outfd = 0;
	return (file);
}

t_redirect	ft_redirect(char *line)
{
	t_redirect	file;

	file = ft_init_redirect();
	if (!line)
		return (file);
	file.infile = ft_file(line, '<');
	file.outfile = ft_file(line, '>');
	while (file.infile)
	{
		printf("infile %s\n", file.infile->content);
		// file.infd = open(file.infile->content, O_RDONLY);
		// if (file.infd == -1)
		// 	perror("open");
		file.infile = ft_next(file.infile);
	}
	while (file.outfile)
	{
		printf("outfile %s\n", file.outfile->content);
		// file.outfd = open(file.outfile->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		// if (file.outfd == -1)
		// 	perror("open");
		file.outfile = ft_next(file.outfile);
	}
	return (file);
}