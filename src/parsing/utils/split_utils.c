#include "../../../inc/minishell.h"

void	ft_count_words2(char *str, size_t *i, char *set)
{
	char	c;

	if (str[*i] && ft_strchr("\'\"", str[*i]))
	{
		c = str[(*i)++];
		while (str[*i] && c != str[*i])
			(*i)++;
		if (str[*i])
			(*i)++;
	}
	if (str[*i] && !ft_strchr(set, str[*i]) && !ft_strchr("\'\"", str[*i]))
		while (str[*i] && !ft_strchr(set, str[*i]) && !ft_strchr("\'\"", str[*i]))
			(*i)++;
}

void	ft_creat_tab2(char *str, size_t *end, char *set, int e)
{
	char	c;

	if (e == 1)
	{
		c = str[(*end)++];
		while (str[*end] && c != str[*end])
			(*end)++;
		if (str[*end])
			(*end)++;
	}
	if (e == 2)
	{
		while (ft_isspace(str[*end]))
			(*end)--;
		(*end)++;
	}
	if (e == 3)
	{
		if (str[*end] && ft_strchr("\'\"", str[*end]))
			ft_creat_tab2(str, end, set, 1);
		if (str[*end] && !ft_strchr(set, str[*end])
			&& !ft_strchr("\'\"", str[*end]))
			while (str[*end] && !ft_strchr(set, str[*end])
				&& !ft_strchr("\'\"", str[*end]))
				(*end)++;
	}
}
