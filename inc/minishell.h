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
	int		lastret;
	int 	prioret;
	int		isprio;
	int		doandand;
	t_cmd	*cmd;
}	t_data;

char	**ft_split2(char *str, char *set);
char	*ft_onespace(char *line);

t_data	*ft_datanew(char	*line);
t_data	*ft_datalast(t_data *data);
void	ft_dataadd_back(t_data **data, t_data *new);

char	**ft_split2(char *str, char *set);
char	*ft_onespace(char *line);
char	*ft_epur_str(char *line);
int		ft_str_isspace(char *str);
void	ft_error(int e);

int		ft_free(char *line);

int	pipex(t_env *data, char *cmd);
void	puterror(char *str);
void	*ft_memdel(void *ptr);

int cmdlexer(char *cmd, t_env *d_env);

char **sort_exp(char **env);

void tokenize(char *line);
char	*ft_pgross_str(char *line);
char	*ft_epur_str(char *line);
int execute(char **input, t_data *data, t_env *d_env);


//================================================================

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

char	*ft_trijoin(char *s1, char *s2, char *s3);
int		ft_exist(char *str, size_t len);
char	*ft_lstmerge(t_list *lst);
char	*ft_woquote(char *line);
char	*ft_replace(char *str, char *search, char *replace);

void	ft_error(int e);
int		ft_free(char *line);
void	ft_free_tab(char **tab);

char	*ft_trijoin1(char *s1, char *s2, char *s3);
char	*ft_trijoin2(char *s1, char *s2, char *s3);
char	*ft_trijoin3(char *s1, char *s2, char *s3);

char	*ft_strjoin1(char const *s1, char const *s2);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_strjoin3(char const *s1, char const *s2);

int	pipex(t_env *data, char *cmd);
void	puterror(char *str);
void	*ft_memdel(void *ptr);

int cmdlexer(char *cmd, t_env *d_env);

char **sort_exp(char **env);

void tokenize(char *line);
char	*ft_pgross_str(char *line);
char	*ft_epur_str(char *line);
int execute(char **input, t_data *data, t_env *d_env);
char	*ft_strjoin2(char const *s1, char const *s2);
int		ft_strncmp2(const char *s1, const char *s2, size_t n);
int		ft_strrcmp2(const char *s1, const char *s2, size_t n);
int print_env(char **env);
void print_exp(char **env, t_env *data);
int my_setenv(char *name, char *value, t_env *data);

#endif
