#include "../../inc/minishell.h"

int subshell(char *line, t_data *data)
{
    int ret;

    line = tokenize(ft_chdir(ft_chwc(ft_chdollar(ft_epur_str(ft_pgross_str(line))))));
    char **res = ft_split(line, "\1");
    ret = execute(res, data);
    exit(ret);
}
//    echo test0 || (echo test1 || echo test2) | echo test3
