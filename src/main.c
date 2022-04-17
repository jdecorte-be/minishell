#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	char	**tab;

	while (1)
	{
		line = readline("bsh-0.01$> ");
		if (!ft_strcmp(line, "exit") && ft_str_isspace(line) && ft_free(line))
			exit(0);
		data.line = ft_epur_str(line);
		data.cmd = ft_creat_cmd(data);
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
