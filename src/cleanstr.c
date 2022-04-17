#include "../inc/minishell.h"

char *tokenize(char *line)
{
	size_t i = 0;

	if (!line)
		return NULL;
	char *res = ft_ecrase_q(ft_strjoin(ft_strjoin(" ", line), " "));
	while(res[i])
	{
		if (((res[i] == '&' && res[i + 1] == '&') || (res[i] == '|' && res[i + 1] == '|')) && res[i + 2] && res[i - 1])
		{
			res[i + 2] = 1;
			res[i - 1] = 1;
		}
		else if((res[i] == '(' || res[i] == ')'))
		{
			res[i + 1] = 1;
			res[i - 1] = 1;
		}
		i++;
	}

	return res;
}
