// #include "../../inc/minishell.h"

// char	*ft_ecrase_p(char *line)
// {
// 	char	*str;
// 	size_t	start;
// 	size_t	end;

// 	if (!line)
// 		return (line);
// 	str = 0;
// 	end = 0;
// 	while (line[end])
// 	{
// 		start = end;
// 		if (line[end] && ft_strchr("\"\'", line[end]))
// 		{
// 			ft_skip_q(line, &end);
// 			str = ft_strjoin1(str, ft_substr(line, start, end - start));
// 		}
// 		else if (line[end] && line[end] == '(')
// 		{
// 			ft_skip_p(line, &end);
// 			start += 2;
// 			str = ft_strjoin1(str, ft_substr(line, start, end - start - 2));
// 		}
// 		else
// 		{
// 			while (line[end] && line[end] != '(' && !ft_strchr("\"\'", line[end]))
// 				end++;
// 			str = ft_strjoin1(str, ft_substr(line, start, end - start));
// 		}
// 	}
// 	return (str);
// }

// char    *ft_ecrase_q(char *word)
// {
// 	char	*new_word;
// 	size_t	i;
// 	size_t	start;
// 	size_t	end;
// 	char	c;

// 	if (!word)
// 		return (0);
// 	i = 0;
// 	end = 0;
// 	new_word = 0;
// 	while (word[end])
// 	{
// 		c = 0;
// 		start = end;
// 		if (word[end] && ft_strchr("\'\"", word[end]))
// 		{
// 			c = word[end++];
// 			start = end;
// 			while (word[end] && word[end] != c)
// 				end++;
// 			new_word = ft_strjoin1(new_word, ft_substr(word, start, end - start));
// 			if (word[end])
// 				end++;
// 		}
// 		else
// 		{
// 			while (word[end] && !ft_strchr("\'\"", word[end]))
// 				end++;
//  			new_word = ft_strjoin1(new_word, ft_substr(word, start, end - start));
// 		}
// 	}
// 	return (new_word);
// }

// char *tokenize(char *line)
// {
// 	size_t i = 0;
// 	int in_par = 0;
// 	if (!line)
// 		return NULL;
// 	char *res = ft_ecrase_q(ft_strjoin(ft_strjoin(" ", line), " "));
// 	while (res[i])
// 	{
// 		if (res[i] == '(')
// 			in_par++;
// 		if (in_par == 0 && ((res[i] == '&' && res[i + 1] == '&') || (res[i] == '|' && res[i + 1] == '|')))
// 		{
// 			res[i + 2] = 1;
// 			res[i - 1] = 1;
// 		}
// 		else if ((in_par == 0 && (res[i] == '>' || res[i] == '<' || (res[i] == '|' && res[i + 1] == ' '))) || res[i] == '(' || res[i] == ')')
// 		{
// 			res[i + 1] = 1;
// 			res[i - 1] = 1;
// 		}
// 		if (res[i] == ')')
// 			in_par--;
// 		i++;
// 	}

// 	return res;
// }
