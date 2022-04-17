#include "../inc/minishell.h"

// char *tokenize(char *line)
// {
// 	size_t i = 0;
// 	int in_par = 0;
// 	if (!line)
// 		return NULL;
// 	char *res = ft_ecrase_q(ft_strjoin(ft_strjoin(" ", line), " "));
// 	while(res[i])
// 	{
// 		if(res[i] == '(')
// 			in_par++;
// 		if (in_par == 0 && ((res[i] == '&' && res[i + 1] == '&') || (res[i] == '|' && res[i + 1] == '|')))
// 		{
// 			res[i + 2] = 1;
// 			res[i - 1] = 1;
// 		}
// 		else if((in_par == 0 && (res[i] == '>' || res[i] == '<' || (res[i] == '|' && res[i + 1] == ' '))) || res[i] == '(' || res[i] == ')')
// 		{
// 			res[i + 1] = 1;
// 			res[i - 1] = 1;
// 		}
// 		if(res[i] == ')')
// 			in_par--;
// 		i++;
// 	}

// 	return res;
// }
// char *tokenize(char *line)
// {
// 	size_t i = 0;

// 	if (!line)
// 		return NULL;
// 	// char *res = ft_ecrase_q(ft_strjoin(ft_strjoin(" ", line), " "));
// 	while(line[i])
// 	{
// 		if (line[i] && line[i + 1] && ((line[i] == '&' && line[i + 1] == '&') || (line[i] == '|' && line[i + 1] == '|')))
// 		{
// 			if (line[i + 2])
// 				line[i + 2] = 1;
// 			if (i)
// 				line[i - 1] = 1;
// 		}
// 		else if (line[i] && (line[i] == '(' || line[i] == ')'))
// 		{
// 			if (line[i + 1])
// 				line[i + 1] = 1;
// 			if (i)
// 				line[i - 1] = 1;
// 		}
// 		i++;
// 	}

// 	return line;
// }

char *tokenize(char *line)
{
	size_t	i;
	int		par;
	char	c;
	
	if (!line)
		return (line);
	i = 0;
	par = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '(')
			ft_skip_p(line, &i);
		else if (line[i] && ft_strchr("\'\"", line[i]))
			ft_skip_q(line, &i);
		else if (line[i] && line[i + 1] && (ft_strnstr(line + i, "&&", 2) || ft_strnstr(line + i, "||", 2)))
		{
			if (i)
				line[i - 1] = 1;
			if (line[i + 2])
				line[i + 2] = 1;
			i += 2;
		}
		else if (line[i] && line[i] == '|')
		{
			if (i)
				line[i - 1] = 1;
			if (line[i + 1])
				line[i + 1] = 1;
			i++;
		}
		else
			i++;
	}
	return (line);
}