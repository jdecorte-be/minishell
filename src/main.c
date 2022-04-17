#include "../inc/minishell.h"

void	ft_signal(int sig);

int	main(int argc, char **argv, char **envp)
{
	t_token	*tmp;
	t_data	data;
	char	*line;
	char	**tab;
	pid_t	pid;
	t_token	*token;
	t_redirect	redirect;


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
		data.line = ft_epur_str(ft_chwc(ft_add_q_dollar(ft_chdir(ft_chdollar(ft_pgross_str((line)))))));
		// printf("!\n");
		// data.line = ft_ecrase_p(data.line);
		token = ft_parsing(data.line);
		while (token)
		{
			printf("%s\n", token->cmd);
			printf("%d\n", token->redirect.infd);
			printf("%d\n", token->redirect.outfd);
			if (token->sub_token)
				token = token->sub_token;
			else if (token->next)
				token = token->next;
			else if (!token->next && token->sup_token)
				token = token->sup_token->next;
			else
				token = token->next;
		}
		// data.line = tokenize(data.line);
		// tab = ft_split(data.line, "\1");
		// token = ft_tab_to_token(tab);
		// tmp = token;
		// while (tmp)
		// {
		// 	printf("%s\n", tmp->cmd);
		// 	tmp = tmp->next;
		// }
		// while (tmp)
		// {
		// 	tmp->redirect = ft_redirect(tmp->cmd);
		// 	tmp->cmd = ft_cut_chevron(tmp->cmd);
		// 	tmp = tmp->next;
		// }
		// while (token)
		// {
		// 	printf("|%s|\n", token->cmd);
		// 	token = token->next;
		// }
		// lsttoken = ft_tokennew(tab[0]);
		// while (redirect.infile)
		// {
		// 	printf("%s\n", redirect.infile->content);
		// 	redirect.infile = redirect.infile->next;
		// }
		// while (redirect.infile)
		// {
		// 	printf("%s\n", redirect.infile->content);
		// 	redirect.infile = redirect.infile->next;
		// }
		// data.line = ft_cutoff(line, 5, 5);
		// while (*tab)
		// 	printf("|%s|\n", *tab++);
		// printf("%s|\n", data.line);
		// free(data.line);
		// line = 0;
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
