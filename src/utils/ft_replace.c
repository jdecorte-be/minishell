#include "../../inc/minishell.h"

char	*ft_replace(char *str, char *search, char *replace)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	len;
	char	*ret;

	i = 0;
	end = 0;
	ret = 0;
	while (str[end])
	{
		start = end;
		len = ft_strlen(search);
		if (!ft_strrcmp(str + end, search, len - 1))
		{
			while (str[end] && !ft_strrcmp(str + end, search, len - 1))
				end++;
			ret = ft_strjoin(ret, ft_substr(str, start, end - start - 1));
		}
		if (str[end] && ft_strrcmp(str + end, search, len - 1))
			ret = ft_strjoin(ret, replace);
	}
	return (ret);
}
