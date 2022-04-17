#include "../inc/minishell.h"

void	puterror(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
	exit(0);
}

void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

int printList(t_list *head)
{
	t_list *tmp = head;

	while(tmp != NULL){
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
	return 0;
}
