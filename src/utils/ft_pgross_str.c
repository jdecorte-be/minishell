#include "../../inc/minishell.h"

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
	char	c;

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
