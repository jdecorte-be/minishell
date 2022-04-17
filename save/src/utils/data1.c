#include "../../inc/minishell.h"

// t_data	*ft_datanew(char	*line)
// {
// 	t_data	*data;

// 	data = malloc(sizeof(data));
// 	if (!data)
// 		ft_error(2);
// 	data->line = line;
// 	data->cmd = 0;
// 	return (data);
// }

// t_data	*ft_datalast(t_data *data)
// {
// 	t_data	*tmp;

// 	tmp = data;
// 	if (tmp)
// 		while (tmp->next)
// 			tmp = tmp->next;
// 	return (tmp);
// }

// void	ft_dataadd_back(t_data **data, t_data *new)
// {
// 	if (!*data)
// 		*data = new;
// 	if (new)
// 		ft_datalast(*data)->next = new;
// }
