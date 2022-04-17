#include "../../inc/minishell.h"

char	*ft_purge_q(char *line)
{
	size_t	end;
	size_t	start;
	char	*str;

	end = 0;
	str = 0;
	while (line[end])
	{
		start = end;
		if (ft_strchr("\'\"", line[end]) && line[end + 1] && line[end + 1] == line[end])
		{
			end += 2;
			start = end;
		}
		else if (ft_strchr("\'\"", line[end]))
			ft_skip_q(line, &end);
		else
		{
			while (line[end] && !ft_strchr("\'\"", line[end]))
				end++;
		}
		if (start != end)
			str = ft_strjoin2(str, ft_substr(line, start, end - start));
	}
	printf("str == %s\n", str);
	return (str);
}