#include "../../inc/minishell.h"

t_cmd	*ft_cmdnew(char	*line)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(cmd));
	if (!cmd)
		ft_error(2);
	cmd->next = 0;
	cmd->line = line;
	cmd->p = 0;
	cmd->n = 0;
	cmd->mcmd = 0;
	return (cmd);
}

t_cmd	*ft_cmdlast(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (cmd)
	{
		tmp = cmd;
		while (tmp->next)
			tmp = tmp->next;
	}
	return (tmp);
}

void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last_elem;

	if (cmd && new)
	{
		if (!*cmd)
			*cmd = new;
		else
		{
			last_elem = ft_cmdlast(*cmd);
			last_elem->next = new;
		}
	}
}
