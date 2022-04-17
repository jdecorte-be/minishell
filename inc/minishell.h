#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/builtins/builtins.h"
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

typedef struct s_sep
{
	char	p;
	char	n;
}	t_sep;

typedef struct s_fd
{
	int	in;
	int	out;
}	t_fd;

typedef struct s_file
{
	char	**in;
	char	**out;
	char	*in_open_mode;
}	t_file;

typedef struct s_here_doc
{
	char				*rule;
	struct s_here_doc	*next;
}	t_here_doc;

typedef struct s_mcmd//	cmd   ((ls )| cat)
{
	char			*line;
	char			*path;
	t_here_doc		*here_doc;
	char			**cmdv;
	t_sep			sep;
	t_fd			fd;
	t_file			file;
	struct s_mcmd	*next;
}	t_mcmd;

typedef struct s_cmd
{
	char			*line;
	char			p;
	char			n;
	struct s_mcmd	*mcmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data//  block de cmd  
{
	char	*line;// ls  //after prompt, without \32\32 space, "" or ''
	int		lastret;
	t_cmd	*cmd;
}	t_data;

t_data	*ft_datanew(char	*line);
t_data	*ft_datalast(t_data *data);
void	ft_dataadd_back(t_data **data, t_data *new);

char	**ft_split2(char *str, char *set);
char	*ft_onespace(char *line);
int		ft_free(char *line);


void	exec(char *cmd, char **env);
int		pipex(t_env *data, char *cmd);
void	puterror(char *str);
void	*ft_memdel(void *ptr);

int cmdlexer(char **cmd, t_env *d_env);

char **sort_exp(char **env);



#endif
