#include "libft.h"

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 12) || c == 1)
		return (1);
	return (0);
}
