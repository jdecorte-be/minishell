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
	t_cmd	*last_elem;

	if (!cmd)
		return (0);
	last_elem = cmd;
	while (last_elem->next != NULL)
		last_elem = last_elem->next;
	return (last_elem);
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
	printf("new = %s\n", new->line);
}
