#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*line;
	char	**tab;

	data = 0;
	while (1)
	{
		line = readline("bsh-0.01$> ");
		if (!ft_strcmp(line, "exit") && ft_free(line))
			exit(0);
		if (line && *ft_strtrim(line, "\t\n\v\f\r "))
			data = ft_datanew(ft_strtrim(line, "\t\n\v\f\r "));
		else
			ft_split2(line, " \t\v\r\f\n");
			ft_dataadd_back(&data, ft_datanew(ft_strtrim(line, "\t\n\v\f\r ")));
		free(line);
		
	}
	// int i = 0;
	// tab = ft_split2(line, "\t\f\r\v\n ");
	// while(tab[i])
	// {
	// 	printf("|%s|\n", tab[i]);
	// 	i++;
	// }
	// printf("")
}
