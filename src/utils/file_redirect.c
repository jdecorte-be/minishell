#include "../../inc/minishell.h"

int	ft_redirect_check(t_redirect file)
{
	t_list	*tmp;
	char	c;
	int		fd;

	tmp = file.infile;
	while (tmp)
	{
		c = ft_strstrchr(tmp->content, "|&()");
		if (c != 0)
		{

			// printf("1\n");
			// dup2(2, 1);
			printf("bash: syntax error near unexpected token `%c'\n", c);
			return (0);
		}
		tmp = tmp->next;
	}
	tmp = file.outfile;
	while (tmp)
	{
		c = ft_strstrchr(tmp->content, "|&()");
		if (c != 0)
		{

			// printf("1\n");
			// dup2(2, 1);
			printf("bash: syntax error near unexpected token `%c'\n", c);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	nothing(void)
{
}


char	*ft_chrredirect(char *line, char c, int *open, size_t *v)
{
	size_t	end;
	size_t	start;
	int		i;

	end = 0;
	i = 2;
	if (line[end] == '<')
		end++;
	else
		while (line[end] == '>' && i--)
			end++;
	if (i == 0)
		*open = 1;
	while (ft_isspace(line[end]))
		end++;
	start = end;
	while (line[end] && !ft_isspace(line[end]))
		end++;
	*v = end;
	return (ft_substr(line, start, end - start));//remplacer le 0 par start; et end par end - start;
}

t_list	*ft_file(char *line, char c, int *open)
{
	t_list	*lst;
	size_t	i;
	char	*str;
	size_t	v;

	v = 0;
	lst = 0;
	i = 0;
	while (line[i])
	{
		// if (*line && *(line + 1) && ft_strncmp(*line, ">>", 1))
		// if (*line && *(line + 1) && ft_strncmp(line + i, "<<", 1))
		// 	i++;
		if (line[i] && ft_strchr("\'\"", line[i]))
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				i++;
			if (line[i])
				i++;
		}
		if (line[i] && ft_strchr("(", line[i]) && ++i)
		{
			v = 1;
			while (line[i] && v != 0)
			{
				if (line[i] == '(')
					v++;
				else if (line[i] == ')')
					v--;
				i++;
			}
		}
		else if (line[i] && line[i] == c && line[i + 1] && line[i + 1] != '<')
		{
			v = 0;
			str = ft_chrredirect(line + i, c, open, &v);
			ft_lstadd_back(&lst, ft_lstnew(str));
			i += v;
			// i += ft_strlen(str);
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
	file.outfd = 1;
	file.open = 0;
	return (file);
}

t_redirect	ft_redirect(char *line, t_redirect file, int e, int fd)
{
	// t_redirect	file;
	t_redirect	tmp;

	// fd = dup(1);
	// file = ft_init_redirect();
	if (!line)
		return (file);
	tmp = file;
	file.infile = ft_file(line, '<', &(file.open));
	file.outfile = ft_file(line, '>', &(file.open));
	if (e)
	{
		if (e == 1)
			file.outfd = fd;
		else if (e == 2)
			file.infd = fd;
	}
	// printf("1\n");
	// printf("open == %d\n", file.open);
	if (ft_redirect_check(file))// && dup2(fd, 1))
	{
		while (file.infile)
		{
			// printf("infile %s\n", file.infile->content);
			if (file.infd != tmp.infd)
				close(file.infd);
			file.infd = open(file.infile->content, O_RDONLY);
			if (file.infd == -1)
				perror("open rd");
			file.infile = ft_next(file.infile);
		}
		while (file.outfile)
		{
			// printf("outfile %s\n", (file.outfile->content));
			if (file.outfd != tmp.outfd)
				close(file.outfd);
			if (file.open == 0)
				file.outfd = open(file.outfile->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else if (file.open == 1)
				file.outfd = open(file.outfile->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (file.outfd == -1)
				perror("open wr");
			file.outfile = ft_next(file.outfile);
		}
	}
	return (file);
}