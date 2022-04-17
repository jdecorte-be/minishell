#include "../../inc/minishell.h"

char	*quajoin_1_3(char *s1, const char *s2, char *s3, const char *s4)
{
	char	*str;
	char	*ret;
	
	str = malloc(sizeof(char) * ((ft_strlen(s1), ft_strlen(s2), ft_strlen(s3), ft_strlen(s4)) + 1));
	ret = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	while (*s3)
		*str++ = *s3++;
	while (*s4)
		*str++ = *s4++;
	return (ret);
}