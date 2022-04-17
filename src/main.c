#include "../inc/minishell.h"

void	ft_signal(int sig);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	char	**tab;
	pid_t	pid;

	while (1)
	{
		ft_signal(SIGINT);
		line = readline("caca->");
		if (ft_isprohibited(line))
			exit(EXIT_FAILURE);
		add_history(line);
		if (!line)
			exit(0);
		// 	// break;
		// data.line = ft_epur_str(ft_chwc(ft_chdir(ft_chdollar(ft_pgross_str((line))))));
		// // printf("!\n");
		// data.line = ft_ecrase_q(data.line);
		// data.line = ft_cutoff(line, 5, 5);
		printf("%s|\n", line);
		free(line);
		line = 0;
		// data.cmd = ft_creat_cmd(data.line);
		// printf("4\n");
	}

	// int i = 0;
	// tab = ft_split2(line, "\t\f\r\v\n ");
	// while(tab[i])
	// {
	// 	printf("|%s|\n", tab[i]);
	// 	i++;
	// }
	// printf("");

	// system("leaks a.out");

	// printf("%d\n", ft_strncmp("da", "da", 100));
}
