// #include "../../inc/minishell.h"

// t_token	*ft_parsing2(t_token *sup_token)
// {
// 	char	**tab;
// 	t_token	*token;
// 	t_token	*tmp;
// 	char	*line;

// 	line = tokenize(ft_ecrase_p(sup_token->cmd));
// 	tab = ft_split(line, "\1");
// 	token = ft_tab_to_token2(tab, sup_token);
// 	tmp = token;
// 	while (tmp)
// 	{
// 		tmp->redirect = ft_redirect(tmp->cmd, sup_token->redirect);
// 		tmp->cmd = ft_cut_chevron(tmp->cmd);
// 		// printf("cmd %s\n", tmp->cmd);
// 		// printf("in %d\n", tmp->redirect.infd);
// 		// printf("out %d\n", tmp->redirect.outfd);
// 		if (tmp->cmd[0] == '(')
// 			tmp->sub_token = ft_parsing2(tmp);
// 		tmp = tmp->next;
// 	}
// 	return (token);
// }

// t_token	*ft_parsing(char *line)
// {
// 	char	**tab;
// 	t_token	*token;
// 	t_token	*tmp;

// 	line = tokenize(line);
// 	tab = ft_split(line, "\1");
// 	token = ft_tab_to_token(tab);
// 	tmp = token;
// 	while (tmp)
// 	{
// 		tmp->redirect = ft_redirect(tmp->cmd, ft_init_redirect());
// 		tmp->cmd = ft_cut_chevron(tmp->cmd);
// 		// printf("cmd %s\n", tmp->cmd);
// 		// printf("in %d\n", tmp->redirect.infd);
// 		// printf("out %d\n", tmp->redirect.outfd);
// 		if (tmp->cmd[0] == '(')
// 			tmp->sub_token = ft_parsing2(tmp);
// 		tmp = tmp->next;
// 	}
// 	return (token);
// }