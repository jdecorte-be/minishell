#include "../inc/minishell.h"

void	ft_signal(int sig);
int	ft_hd_replace(int fd);

int	main(int argc, char **argv, char **envp)
{
	// t_token	*tmp;
	char	*line;
	// char	**tab;
	pid_t	pid;
	t_token	*token;
	t_redirect	redirect;
	int		fd[10];
	char	**tab;
	t_hd	*tmp;
	int		ret;
	// char	*tab2[2];


	data = malloc(sizeof(t_data));
	while (1)
	{
		ft_signal(SIGINT);
		line = readline("caca->");
		ret = ft_isprohibited(line);
		if (ret == 1)
			continue;
		add_history(line);
		if (!line)
			exit(0);
		// 	// break;
		line = ft_epur_str(ft_chdollar((ft_chdir((ft_pgross_str(line))))));
		data->hd = 0;

		// tmp = data->hd;
		// printf("!\n");
		// line = ft_chwc(line);
		// tab = ft_split2(line, "/");
		
		// int	i = 0;
		// while (tab[i])
		// 	printf("%s|\n", tab[i++]);
		// line = ft_ecrase_q(line);

		// tmp = data->hd;
		// while (tmp)
		// {
		// 	printf("tmp == %d\n", tmp->fd);
		// 	tmp = tmp->next;
		// }

		// data->hd = ft_hd_finder(line);

		// token = ft_parsing(line);
		// while (token)
		// {
		// 	if (token->sup_token)
		// 		token->redirect = ft_redirect(token->cmd, token->sup_token->redirect, 0, 0);
		// 	else
		// 		token->redirect = ft_redirect(token->cmd, ft_init_redirect(), 0, 0);
		// 	printf("%s\n", token->cmd);
		// 	printf("%d\n", token->redirect.infd);
		// 	printf("%d\n", token->redirect.outfd);
		// 	// printf("open 1 %d\n", token->redirect.open->fd);
		// 	// printf("open 2 %d\n", token->redirect.open2->fd);
		// 	if (token->sub_token)
		// 		token = token->sub_token;
		// 	else if (token->next)
		// 		token = token->next;
		// 	else if (!token->next && token->sup_token)
		// 		token = token->sup_token->next;
		// 	else
		// 		token = token->next;
		// }
		
		// ft_hd_replace(4);
		// line = get_next_line(4);
		tab = ft_split2(line, " ");
		// hd = ft_sort_hd(hd, line, token);
		size_t i = 0;
		while (tab[i])
			printf("tab = |%s|\n", tab[i++]);
		while (line[i])
			printf("%d\n", line[i++]);
		printf("%s\n", line);







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


		// dup2(3, 0);
		// tab[0] = "cat";
		// tab[1] = 0;
		// execve("/bin/cat", tab, envp);
		// fd[1] = dup(1);
		// fd[0] = dup(0);
		// tab[0] = "cat";
		// tab[1] = "-e";
		// tab[2] = 0;
		// tab2[0] = "ls";
		// tab[1] = 0;
		// pid = fork();
		// if (!pid)
		// {
		// 	// close(4);
		// 	dup2(5, 1);
		// 	execve("/bin/ls", tab2, envp);
		// }
		// wait(0);
		// // dup2(fd[1], 1);
		// close(5);
		// dup2(fd[1], 1);
		// dup2(4, 0);
		// // close(1);
		// execve("/bin/cat", tab, envp);

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
