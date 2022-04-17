#include "../../inc/minishell.h"

int subshell(char *line, t_env *d_env, t_data *data)
{
    line = ft_chdir(ft_chwc(ft_chdollar(ft_epur_str(line))));
    tokenize(line);
    char **res = ft_split(line, "\1");
    return execute(res, data, d_env);
}
//    echo test0 || (echo test1 || echo test2) && echo test3
