#include "../inc/minishell.h"

void	ft_add_cmd_sep(t_cmd **cmd)
{
	t_cmd	*tmp;

	(*cmd)->sep.n = '&';
	tmp = (*cmd)->next;
	while (tmp->next)
	{
		tmp->sep.p = '&';
		tmp->sep.n = '&';
		tmp = tmp->next;
	}
	tmp->sep.p = '&';
}

t_cmd	*ft_creat_cmd(char *line)
{
	t_cmd	*cmd;
	size_t	i;
	size_t	i2;
	char	**tab;
	t_cmd	*tmp;

	cmd = 0;
	printf("a\n");
	tab = ft_split3(line, "&");
	printf("DA\n");
	i = 0;
	while (tab[i])
		printf("tab = %s\n", tab[i++]);
	i = 0;
	while (tab[i])
	{
		printf("tab[i] = %s\n", tab[i]);
		ft_cmdadd_back(&cmd, ft_cmdnew(tab[i++]));
	}
	printf("b\n");
	if (i > 1)
		ft_add_cmd_sep(&cmd);
	printf("c\n");
	tmp = cmd;
	while (tmp)
	{
		printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->line);
	// 	tmp->mcmd = ft_creat_mcmd(tmp->line);
	// 	tmp = tmp->next;
	// }
	return (cmd);
}
