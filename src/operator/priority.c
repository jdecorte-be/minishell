#include "../../inc/minishell.h"

int subshell(char *line, t_data *data)
{
    line = tokenize(ft_chdir(ft_chwc(ft_chdollar(ft_epur_str(line)))));
    tokenize(line);
    char **res = ft_split(line, "\1");
    exit(execute(res, data));
}
//    echo test0 || (echo test1 || echo test2) | echo test3
