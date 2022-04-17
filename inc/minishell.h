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
# include <limits.h>
# include <dirent.h>

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
	t_cmd	*cmd;
}	t_data;

t_cmd	*ft_cmdnew(char	*line);
t_cmd	*ft_cmdlast(t_cmd *cmd);
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new);

t_mcmd	*ft_mcmdnew(char *line);
t_mcmd	*ft_mcmdlast(t_mcmd *mcmd);
void	ft_mcmdadd_back(t_mcmd **mcmd, t_mcmd *new);

char	**ft_split2(char *str, char *set);
char	*ft_onespace(char *line);
char	*ft_epur_str(char *line);
int		ft_str_isspace(char *str);

void	ft_creat_tab2(char *str, size_t *end, char *set, int e);
void	ft_count_words2(char *str, size_t *i, char *set);
char	**ft_split3(char *str, char *set);

t_cmd	*ft_creat_cmd(char *line);
t_mcmd	*ft_creat_mcmd(char *line);
char	*ft_pgross_str(char *line);
char	*ft_chdollar(char *line);

char	**ft_split4(char *str, char *set);
char	*ft_chwc(char *line);
char	*ft_wcfile(char *wc);
t_list	*ft_wcsearch(char *line);

int		ft_exist(char *str, size_t len);

void	ft_error(int e);
int		ft_free(char *line);

#endif
