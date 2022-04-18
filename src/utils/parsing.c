#include "../../inc/minishell.h"

t_token	*ft_parsing2(t_token *sup_token)
{
	char	**tab;
	t_token	*token;
	t_token	*tmp;
	char	*line;
	int		fd[2];

	line = tokenize(ft_ecrase_p(sup_token->cmd));
	tab = ft_split(line, "\1");
	token = ft_tab_to_token2(tab, sup_token);
	tmp = token;
	while (tmp)
	{
		// if (tmp->next && !ft_strcmp(tmp->next->cmd, "|"))
		// {
		// 	if (pipe(fd) == -1)
		// 		ft_error(3);
		// 	tmp->redirect = ft_redirect(tmp->cmd, sup_token->redirect, 1, fd[1]);
		// }
		// else if (!ft_strcmp(tmp->cmd, "|"))
		// {
		// 	tmp = tmp->next;
		// 	tmp->redirect = ft_redirect(tmp->cmd, sup_token->redirect, 2, fd[0]);
		// }
		// else
		tmp->redirect = ft_redirect(tmp->cmd, sup_token->redirect, 0, 0);
		// if (ft_hd_exist(tmp->cmd))
		// {
		// 	ft_here_doc(tmp);
		// 	printf("%d\n", tmp->redirect.infd);
		// }
		tmp->cmd = ft_cut_chevron(tmp->cmd);
		// printf("cmd %s\n", tmp->cmd);
		// printf("in %d\n", tmp->redirect.infd);
		// printf("out %d\n", tmp->redirect.outfd);
		if (tmp->cmd[0] == '(')
			tmp->sub_token = ft_parsing2(tmp);
		tmp = tmp->next;
	}
	return (token);
}

t_token	*ft_parsing(char *line)
{
	char	**tab;
	t_token	*token;
	t_token	*tmp;
	int		fd[2];

	line = tokenize(line);
	tab = ft_split(line, "\1");
	token = ft_tab_to_token(tab);
	tmp = token;
	while (tmp)
	{

		// printf("tmp = %s\n", tmp->cmd);
		// if (tmp->next && !ft_strcmp(tmp->next->cmd, "|"))
		// {
		// 	// printf("1\n");
		// 	if (pipe(fd) == -1)
		// 		ft_error(3);
		// 	tmp->redirect = ft_redirect(tmp->cmd, ft_init_redirect(), 1, fd[1]);
		// }
		// else if (!ft_strcmp(tmp->cmd, "|"))
		// {
		// 	// printf("3\n");
		// 	tmp->redirect = ft_redirect(tmp->cmd, ft_init_redirect(), 0, 0);
		// 	tmp = tmp->next;
		// 	tmp->redirect = ft_redirect(tmp->cmd, ft_init_redirect(), 2, fd[0]);
		// }
		// else
		tmp->redirect = ft_redirect(tmp->cmd, ft_init_redirect(), 0, 0);
		// if (ft_hd_exist(tmp->cmd))
		// {
		// 	ft_here_doc(tmp);
		// 	printf("%d\n", tmp->redirect.infd);
		// }
		tmp->cmd = ft_cut_chevron(tmp->cmd);
		// printf("cmd %s\n", tmp->cmd);
		// printf("in %d\n", tmp->redirect.infd);
		// printf("out %d\n", tmp->redirect.outfd);
		if (tmp->cmd[0] == '(')
			tmp->sub_token = ft_parsing2(tmp);
		tmp = tmp->next;
	}
	return (token);
}

void	ft_redirect_for_john(t_token *token)
{
	token->redirect = ft_redirect(token->cmd, token->redirect, 0, 0);
	if (token->sub_token)
		token->sub_token->redirect = token->redirect;
}
