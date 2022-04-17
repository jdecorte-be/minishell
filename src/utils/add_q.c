#include "../../inc/minishell.h"

char	*ft_add_q_dollar(char *line)
{
	size_t	end;
	size_t	start;
	char	*str;
	int		trig;
	char	c;

	trig = 0;
	end = 0;
	str = 0;
	while (line[end])
	{
		start = end;
		if (!ft_strncmp(line + end, "export ", 6))
		{
			end = ft_next_word(line, end);
			while (line[end] && !ft_isspace(line[end]))
			{
				while (line[end] && !ft_isspace(line[end] && !ft_strchr("\'\"", line[end]) && line[end] != '=' && trig != 1)
					end++;
				if (line[end] && !ft_isspace(line[end]) && ft_strchr("\'\"", line[end]))
				{
					c = line[end++];
					while (line[end] && !ft_isspace(line[end]) && line[end] != c)
					{
						if (line[end] == '=')
							trig = 1;
						end++;
					}
				}
				if (line[end] && !ft_isspace(line[end]) && line[end] == '=')
					trig = 1;
			}
			//pas fini, penser a faire --> export da'da=$ad'$a* ----> export dada="$ad<arg $a>*"
			
			printf("add_q = %s\n", line + end);
			printf("export found\n");
			break;
		}
		// else
		end = ft_next_cmd(line, end);
		str = ft_strjoin1(str, ft_substr(line, start, end - start));
			// end = ft_next_word(line, end);
	}
	return (str);
}






/*

-> export hello=""

*/