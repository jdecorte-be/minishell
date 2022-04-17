#include "../../inc/minishell.h"

char	*ft_cut_chevron(char *str)
{
	char	*tmp;
	size_t	start;
	size_t	end;

	if (!str)
		return (str);
	end = 0;
	while (str[end])
	{
		start = end;
		if (ft_strchr("\"\'", str[end]))
			ft_skip_q(str, &end);
		else if (str[end] == '(')
			ft_skip_p(str, &end);
		else if (ft_strnstr(str + end, "<<", 2))
		{
			write(1, "caac\n", 5);
			end = ft_next_word(str, ft_next_word(str, end));
		}
		else if (ft_strchr("><", str[end]))
		{
			end = ft_next_word(str, ft_next_word(str, end));
			tmp = str;
			str = ft_cutoff(tmp, start, end - start);
			free(tmp);
			end -= end - start;
		}
		else
			end++;
		// printf("end == %zu   start == %zu", end, start);
	}
	// printf("str == %s\n", str);
	return (str);
}