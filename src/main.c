#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	char	**tab;

	while (1)
	{
		printf("1\n");
		line = get_next_line(0);
		printf("2\n");
		data.line = ft_epur_str(line);
		printf("3\n");
		line = 0;
		data.cmd = ft_creat_cmd(data.line);
		printf("4\n");
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
