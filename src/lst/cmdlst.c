#include "../../inc/minishell.h"

t_cmd	*ft_cmdnew(char	*line)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(cmd));
	if (!cmd)
		ft_error(2);
	cmd->next = 0;
	cmd->line = line;
	cmd->sep.p = 0;
	cmd->sep.n = 0;
	cmd->mcmd = 0;
	cmd->next = 0;
	return (cmd);
}

t_cmd	*ft_cmdlast(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	return (tmp);
}

void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	if (new)
	{
		if (!*cmd)
			*cmd = new;
		else
			ft_cmdlast(*cmd)->next = new;
	}
}
