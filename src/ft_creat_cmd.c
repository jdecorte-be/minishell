#include "../inc/minishell.h"

t_cmd	*ft_creat_cmd(char *line)
{
	t_cmd	*cmd;
	size_t	i;
	size_t	i2;
	char	**tab;
	t_cmd	*tmp;

	tab = ft_split3(line, "&&");
	i = 0;
	while (tab[i])
		printf("tab = %s\n", tab[i++]);
	i = 0;
	printf("%s\n", tab[i]);
	cmd = ft_cmdnew(tab[i++]);
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		ft_cmdadd_back(&cmd, ft_cmdnew(tab[i++]));
	}
	tmp = cmd;
	while (tmp)
	{
		printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
	// while (tmp)
	// {
		// tmp->mcmd = ft_creat_mcmd(tmp->line);
	// 	tmp = tmp->next;
	// }
	return (cmd);
}
