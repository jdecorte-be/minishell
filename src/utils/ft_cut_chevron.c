#include "../../inc/minishell.h"

char	*ft_cut_chevron(char *str)
{
	char	*tmp;
	size_t	start;
	size_t	end;
	char	c;

	end = 0;
	while (str[end])
	{
		start = end;
		if (ft_strchr("\"\'", str[end]))
		{
			c = str[end++];
			while (str[end] && str[end] != c)
				end++;
			if (str[end])
				end++;
		}
		else if (ft_strchr("><", str[end]))
		{
			end = ft_next_word(str, ft_next_word(str, end));
			tmp = str;
			str = ft_cutoff(tmp, start, end - start);
			free(tmp);
		}
		else
			end++;
	}
	// printf("str == %s\n", str);
	return (str);
}