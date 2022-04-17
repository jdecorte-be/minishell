#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_data//  block de cmd  
{
	char			*line;// ls  //after prompt, without \32\32 space, "" or ''
	char			**outfile;
	char			**infile;
	int				*infd;		
	int				*outfd;
	struct s_cmd	*cmd;// **cmd = {"ls"}
	struct s_data	*next;
}	t_data;

typedef struct s_cmd//	cmd   (ls | cat)
{
	char			*path;
	char			**cmdv;
	struct s_cmd	*next;
}	t_cmd;

t_data	*ft_datanew(char	*line);
t_data	*ft_datalast(t_data *data);
void	ft_dataadd_back(t_data **data, t_data *new);

char	**ft_split2(char *str, char *set);
char	*ft_onespace(char *line);
void	ft_error(int e);
int		ft_free(char *line);

#endif
