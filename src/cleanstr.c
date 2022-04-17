#include "../inc/minishell.h"

void delete_ext_quotes(char *line)
{
	int i = 0;
	int j = 0;
	int next_index = 0;
	while(line[i])
	{
		if(line[i] == '\"' || line[i] == '\'')
		{
			ft_memmove(&line[i] , &line[i + 1], ft_strlen(line) - i);
			j = i;
			while(line[j])
			{
				if(line[j] == line[i])
					next_index = j;
				i++;
			}
			ft_memmove(&line[next_index] , &line[next_index + 1], ft_strlen(line) - next_index);
			break;
		}
		i++;
	}
}

char *tokenize(char *line)
{
	size_t i = 0;

	if (!line)
		return NULL;
	char *res = ft_strjoin(ft_strjoin(" ", line), " ");
	while(res[i])
	{
		if (((res[i] == '&' && res[i + 1] == '&') || (res[i] == '|' && res[i + 1] == '|')) && res[i + 2] && res[i - 1])
		{
			res[i + 2] = 1;
			res[i - 1] = 1;
		}
		else if((res[i] == '>' || res[i] == '<') || (res[i] == '(' || res[i] == ')'))
		{
			res[i + 1] = 1;
			res[i - 1] = 1;
		}
		i++;
	}
	return res;
}
