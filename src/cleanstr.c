#include "../inc/minishell.h"

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 12))
		return (1);
	return (0);
}

static void	ft_epur_len2(char *line, size_t *i, size_t *count)
{
	char	c;

	c = line[(*i)++];
	while (line[*i] && line[(*i)++] != c)
		(*count)++;
	(*count)++;
}

static size_t	ft_epur_len(char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i] && ft_strchr("\'\"", line[i]) && ++count)
			ft_epur_len2(line, &i, &count);
		while (line[i] && !ft_isspace(line[i]) && !ft_strchr("\'\"", line[i])
			&& ++i)
			count++;
		if (line[i] && ft_isspace(line[i]))
			count++;
	}
	if (!line[i] && i > 0 && line[i - 1] && ft_isspace(line[i - 1]))
		count--;
	return (count);
}

char	*ft_epur_str2(char *str, char *line, size_t *i2, size_t *i)
{
	char	c;

	while (line[*i])
	{
		while (line[*i] && ft_isspace(line[*i]))
			(*i)++;
		if (line[*i] && ft_strchr("\'\"", line[*i]))
		{
			str[(*i2)++] = line[*i];
			c = line[(*i)++];
			while (line[*i] && line[*i] != c)
				str[(*i2)++] = line[(*i)++];
			str[(*i2)++] = line[(*i)++];
		}
		while (line[*i] && !ft_isspace(line[*i]) && !ft_strchr("\'\"", line[*i]))
			str[(*i2)++] = line[(*i)++];
		if (line[*i] && ft_isspace(line[*i]))
			str[(*i2)++] = ' ';
	}
	return (str);
}

char	*ft_epur_str(char *line)
{
	char	*str;
	size_t	i;
	size_t	i2;

	if (!line)
		return (0);
	str = malloc(sizeof(char) * (ft_epur_len(line) + 1));
	if (!str)
		ft_error(2);
	i = 0;
	i2 = 0;
	str = ft_epur_str2(str, line, &i2, &i);
	if (i > 0  && i2 > 0 && ft_isspace(line[i - 1]))
		i2--;
	str[i2] = 0;
	free(line);
	return (str);
}

size_t	ft_pgross_len(char *line)
{
	size_t	i;
	size_t	count;
	char	c;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_strchr("\'\"", line[i]))
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				i++;
			i++;
		}
		else if ((!ft_strncmp(&line[i], "&&", 2)
				|| !ft_strncmp(&line[i], "||", 2)) && ++i && ++i)
			count += 2;
		else if (ft_strchr("()&|", line[i]) && ++i)
			count += 2;
		else
			i++;
	}
	return (i + count);
}

void	ft_pgross_creat3(char *str, size_t *i, size_t *i2, char *line)
{
	str[(*i)++] = ' ';
	str[(*i)++] = line[(*i2)++];
	str[(*i)++] = line[(*i2)++];
	str[(*i)++] = ' ';
}

void	ft_pgross_creat2(char *str, size_t *i, size_t *i2, char *line)
{
	char	c;

	if (ft_strchr("\'\"", line[*i2]))
	{
		c = line[*i2];
		str[(*i)++] = line[(*i2)++];
		while (line[*i2] && line[*i2] != c)
			str[(*i)++] = line[(*i2)++];
		str[(*i)++] = line[(*i2)++];
	}
	else if (!ft_strncmp(&line[*i2], "&&", 2)
		|| !ft_strncmp(&line[*i2], "||", 2))
		ft_pgross_creat3(str, i, i2, line);
	else if (ft_strchr("()|&", line[*i2]))
	{
		str[(*i)++] = ' ';
		str[(*i)++] = line[(*i2)++];
		str[(*i)++] = ' ';
	}
	else
		str[(*i)++] = line[(*i2)++];
}

static char	*ft_pgross_creat(char *str, char *line)
{
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	while (line[i2])
		ft_pgross_creat2(str, &i, &i2, line);
	str[i] = 0;
	return (str);
}

char	*ft_pgross_str(char *line)
{
	char	*newline;
	size_t	len;

	if (!line)
		return (0);
	len = ft_pgross_len(line);
	newline = malloc(sizeof(char) * (len + 1));
	newline = ft_pgross_creat(newline, line);
	free(line);
	return (newline);
}

void tokenize(char *line)
{
	int i = 0;

	if (!line)
		return ;
	while(line[i])
	{
		if(line[i] == '(' || line[i] == ')' || (line[i] == '|' && line[i + 1] != '|' && line[i - 1] != '|'))
		{
			line[i + 1] = 1;
			line[i - 1] = 1;
		}
		else if(line[i] == '&' && line[i + 1] == '&')
		{
			line[i + 2] = 1;
			line[i - 1] = 1;
		}
		else if(line[i] == '|' && line[i + 1] == '|')
		{
			line[i + 2] = 1;
			line[i - 1] = 1;
		}
		i++;
	}

}
