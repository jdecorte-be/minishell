#include "../../inc/minishell.h"

t_mcmd	*ft_mcmdnew(char *line, t_file file)
{
	t_mcmd	*mcmd;

	mcmd = malloc(sizeof(mcmd));
	if (!mcmd)
		ft_error(2);
	mcmd->next = 0;
	mcmd->line = line;
	mcmd->path = 0;//~~~~~~~~~~~~~~~~~~~~
	mcmd->here_doc = 0;//~~~~~~~~~~~~~~~~~~~~
	mcmd->cmdv = ft_split2(line, "\t\n\f\r\v ");//~~~~~~~~~~~~~
	mcmd->sep.p = 0;
	mcmd->sep.n = 0;
	mcmd->fd.in = 0;
	mcmd->fd.out = 1;
	mcmd->file = file;
	return (mcmd);
}

t_mcmd	*ft_mcmdlast(t_mcmd *mcmd)
{
	t_mcmd	*tmp;

	tmp = mcmd;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	return (tmp);
}

void	ft_mcmdadd_back(t_mcmd **mcmd, t_mcmd *new)
{
	if (new)
	{
		if (!*mcmd)
			*mcmd = new;
		else
			ft_mcmdlast(*mcmd)->next = new;
	}
}
