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
	cmd->file.in = 0;
	cmd->file.out = 0;
	cmd->file.in_open_mode = 0;
	cmd->mcmd = 0;
	cmd->next = 0;
	return (cmd);
}

t_data	*ft_datalast(t_data *data)
{
	t_data	*tmp;

	tmp = data;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	return (tmp);
}

void	ft_dataadd_back(t_data **data, t_data *new)
{
	if (new)
	{
		if (!*data)
			*data = new;
		else
			ft_datalast(*data)->next = new;
	}
}
