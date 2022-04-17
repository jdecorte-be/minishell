#include "../inc/minishell.h"

t_mcmd	*ft_creat_mcmd(char *line)
{
	t_mcmd	*mcmd;
	char	**tab;
	size_t	i;
	t_mcmd	*tmp;

	i = 0;
	mcmd = 0;
	tab = ft_split3(line, "|");
	// while (tab[i])
	// {
	// 	ft_mcmdadd_back(&mcmd, ft_mcmdnew(tab[i++]));
	// }
	// tmp = mcmd;
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->line);
	// 	tmp = tmp->next;
	// }
	return (mcmd);
}