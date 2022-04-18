#include "../../inc/minishell.h"

static size_t	ft_count_words(char *str, char *set)
{
	size_t	i;
	size_t	count;
	char	c;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && ft_strchr(set, str[i]))
			i++;
		if (str[i] && !ft_strchr(set, str[i]) && ++count)
			while (str[i] && !ft_strchr(set, str[i]))
				ft_count_words2(str, &i, set);
	}
	return (count);
}
// static size_t	ft_count_words(char *str, char *set)
// {
// 	size_t	i;
// 	size_t	count;
// 	char	c;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] && ft_strchr(set, str[i]))
// 			i++;
// 		else if (str[i] && !ft_strchr(set, str[i]) && ++count)
// 		{
// 			if (str[i] && ft_strchr("\'\"", str[i]))
// 			{
// 				c = str[i++];
// 				while (str[i] && c != str[i])
// 					i++;
// 				i++;
// 			}
// 			if (!ft_strchr(set, str[i]))
// 				while (str[i] && !ft_strchr(set, str[i]))
// 					i++;
// 		}
// 	}
// 	return (count);
// }

static char	**ft_creat_tab(char **tab, char *str, char *set, size_t word)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	c;

	i = 0;
	end = 0;
	while (i < word)
	{
		start = end;
		while (str[start] && ft_strchr(set, str[start]))
			start++;
		end = start;
		if (str[end] && !ft_strchr(set, str[end]))
		{
			while (str[end] && !ft_strchr(set, str[end]))
			{
				if (ft_strchr("\'\"", str[end]))
					ft_skip_q(str, &end);
				else
					end++;
			}
		}
		tab[i++] = ft_substr(str, start, end - start);
	}
	tab[i] = 0;
	return (tab);
}

char	**ft_split2(char *str, char *set)
{
	char	**tab;
	size_t	word;

	if (!str && !*str)
		return (0);
	word = ft_count_words(str, set);
	printf("word = %zu\n", word);
	tab = malloc(sizeof(char *) * (word + 1));
	if (!tab)
		ft_error(2);
	return (ft_creat_tab(tab, str, set, word));
}
