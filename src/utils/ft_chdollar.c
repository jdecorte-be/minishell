#include "../../inc/minishell.h"

int	ft_chdollar_ok(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '\"' && ++i)
		{
			while (line[i] && line[i] != '\"')
			{
				if (line[i] && line[i] == '$')
					return (0);
				i++;
			}
			if (line[i])
				i++;
		}
		else if (line[i] && line[i] == '\'')
			ft_skip_q(line, &i);
		else if (line[i] && line[i] == '$')
			return (0);
		else if (line[i])
			i++;
	}
	return (1);
}

char	*ft_changedollar(char *line, t_list **dollar)
{
	char	*str;

	// printf("%s\n", line);
	if (ft_isdigit(line[0]))
		str = 0;
	else if (ft_strncmp(line, "$?", 1))
		str = ft_strdup(getenv(line + 1));
	else if (!ft_strncmp(line, "$?", 1))
		str = ft_itoa(data->lastret);
	else
		str = 0;
	ft_lstadd_back(dollar, ft_lstnew(str));
	free(line);
	return (str);
}

// char	*ft_changedollar2(char *line, t_list **dollar)
// {
// 	char	*str;

// 	if (ft_strcmp(line, "$-"))
// 	{
// 		str = ft_strdup(getenv(line + 1));
// 		if (str)
// 			str = ft_trijoin("\'", str, "\'");
// 	}
// 	else
// 		str = "\'569JNRXZghiklms\'";
// 	ft_lstadd_back(dollar, ft_lstnew(str));
// 	return (str);
// }

size_t	ft_chdollar_len(char *line, t_list **dollar)
{
	size_t	i;
	long	count;
	long	start;
	long	end;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_strchr("\'\"", line[i]))
		{
			if (line[i] == '\'' && ++i)
			{
				while (line[i] && line[i] != '\'')
					i++;
				i++;
			}
			else if (line[i] == '\"' && ++i)
			{
				while (line[i] && line[i] != '\"')
				{
					while (line[i] && line[i] != '\"' && line[i] != '$')
						i++;
					if (line[i] && line[i] != '\"' && line[i + 1] && line[i] == '$' && (ft_isalnum(line[i + 1]) || ft_strchr("?", line[i + 1])))//!ft_strchr("\n\f\v\r\t \"+/%^~:.,   …•¶§∞¢£™¡", line[i + 1]))
					{
						start = i++;
						if (line[i] && line[i] != '\"' && (line[i] == '?' || ft_isdigit(line[i])) && ++i)
						{
							end = i;
							count += start - end;
							count += ft_strlen(ft_changedollar(ft_substr(line, start, end - start), dollar));
						}
						else if (line[i] != '\"')
						{
							// if (line[i] && !ft_strchr("\"\'+/%^~:.,-", line[i]) && !ft_isspace(line[i]))
							// 	i++;
							while (line[i] && line[i] != '\"' && (ft_isalnum(line[i]) || ft_strchr("?", line[i])))//!ft_strchr("\"\'+/%^~:.,-", line[i]) && !ft_isspace(line[i]))
								i++;
							end = i;
							count += start - end;
							count += ft_strlen(ft_changedollar(ft_substr(line, start, end - start), dollar));
						}
					}
					else if (line[i] && line[i] != '\"')
						i++;
				}
				if (line[i] && line[i])
					i++;
			}
		}
		else if (line[i] && line[i + 1] && line[i] == '$' && (ft_isalnum(line[i + 1]) || ft_strchr("?", line[i + 1])))//!ft_strchr("\n\f\v\r\t \"+/%^~:.,   …•¶§∞¢£™¡", line[i + 1]))
		{
			start = i++;
			if (ft_strchr("\'\"", line[i]) && ++i)
				count--;
			else if (line[i] == '?' || ft_isdigit(line[i]))
			{
				count += -2;
				count += ft_strlen(ft_changedollar(ft_substr(line, start, end - start), dollar));
			}
			else
			{
				// if (line[i] && !ft_strchr("\"\'+/%^~:.,-", line[i]) && !ft_isspace(line[i]))
				// 	i++;
				while (line[i] && (ft_isalnum(line[i]) || ft_strchr("?", line[i])))//!ft_strchr("\"\'+/%^~:.,-", line[i]) && !ft_isspace(line[i]))
					i++;
				end = i;
				count += start - end;
				count += ft_strlen(ft_changedollar(ft_substr(line, start, end - start), dollar));
			}
		}
		else
			i++;
	}
	return (i + count);
}

char	*ft_chdollar_str(char *str, char *line, t_list *dollar, size_t len)
{
	size_t	i;
	size_t	i2;
	t_list	*tmp;

	i = 0;
	i2 = 0;
	while (line[i])
	{
		if (ft_strchr("\'\"", line[i]))
		{
			if (line[i] == '\'')
			{
				str[i2++] = line[i++];
				while (line[i] && line[i] != '\'')
					str[i2++] = line[i++];
				str[i2++] = line[i++];
			}
			else if (line[i] == '\"')
			{
				str[i2++] = line[i++];
				while (line[i] && line[i] != '\"')
				{
					while (line[i] && line[i] != '\"' && line[i] != '$')
						str[i2++] = line[i++];
					if (line[i] && line[i] != '\"' && line[i + 1] && line[i] == '$' && (ft_isalnum(line[i + 1]) || ft_strchr("_?", line[i + 1])) && ++i)//!ft_strchr("\n\f\v\r\t \"+/%^~:.,   …•¶§∞¢£™¡", line[i + 1]))
					{
						if (line[i] && line[i] != '\"' && (line[i] == '?' || ft_isdigit(line[i])) && ++i)
						{
							i2 = ft_strlcat(str, dollar->content, len);
							dollar = ft_next(dollar);
						}
						else if (line[i] != '\"')
						{
							// if (line[i] && !ft_strchr("\"\'+/%^~:.,-", line[i]) && !ft_isspace(line[i]))
							// 	i++;
							while (line[i] && line[i] != '\"' && (ft_isalnum(line[i]) || ft_strchr("?", line[i])))//!ft_strchr("\"\'+/%^~:.,-=\'\"", line[i]) && !ft_isspace(line[i]))
								i++;
							i2 = ft_strlcat(str, dollar->content, len);
							// printf("1\n");
							dollar = ft_next(dollar);
						}
					}
					else if (line[i] && line[i] != '\"')
						str[i2++] = line[i++];
				}
				if (line[i])
					str[i2++] = line[i++];
			}
		}
		else if (line[i] && line[i + 1] && line[i] == '$' && (ft_isalnum(line[i + 1]) || ft_strchr("?", line[i + 1])) && ++i)//!ft_strchr("\n\f\v\r\t \"+/%^~:.,   …•¶§∞¢£™¡", line[i + 1]) && ++i)
		{
			if ((line[i] == '?' || ft_isdigit(line[i])) && ++i)
			{
				i2 = ft_strlcat(str, dollar->content, len);
				dollar = ft_next(dollar);
			}
			else
			{
				// if (line[i] && !ft_strchr("\"\'+/%^~:.,-", line[i]) && !ft_isspace(line[i]))
				// 	i++;
				while (line[i] && (ft_isalnum(line[i]) || ft_strchr("?", line[i])))//!ft_strchr("+/%^~:.,-=\'\"", line[i]) && !ft_isspace(line[i]))
					i++;
				i2 = ft_strlcat(str, dollar->content, len);
				dollar = ft_next(dollar);
			}
		}
		else if (line[i] && line[i] == '$' && line[i + 1] && ft_strchr("\'\"", line[i + 1]))
			i++;
		else if (line[i])
		{
			str[i2++] = line[i++];
		}
	}
	str[i2] = 0;
	return (str);
}

char	*ft_chdollar(char *line)
{
	size_t	len;
	char	*str;
	t_list	*dollar;

	if (!line)
		return (0);
	if (ft_chdollar_ok(line))
		return (line);
	dollar = 0;
	len = ft_chdollar_len(line, &dollar);
	str = ft_calloc(sizeof(*str), len + 1);
	str = ft_chdollar_str(str, line, dollar, len);
	free(line);
	// printf("str == %s\n", str);
	return (str);
}
