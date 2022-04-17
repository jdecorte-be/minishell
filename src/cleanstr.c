#include "../inc/minishell.h"

void tokenize(char *line)
{
	int i = 0;

	if (!line)
		return ;
	while(line[i])
	{
		if(line[i] == '(' || line[i] == ')' || (line[i] == '|' && line[i + 1] != '|' && line[i - 1] != '|'))
		{
			line[i + 1] = 1;
			line[i - 1] = 1;
		}
		else if(line[i] == '&' && line[i + 1] == '&')
		{
			line[i + 2] = 1;
			line[i - 1] = 1;
		}
		else if(line[i] == '|' && line[i + 1] == '|')
		{
			line[i + 2] = 1;
			line[i - 1] = 1;
		}
		i++;
	}
}
