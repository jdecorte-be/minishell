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

typedef struct s_redirect
{
	t_list	*infile;
	t_list	*outfile;
	int		infd;
	int		outfd;
	int		open;
}	t_redirect;

typedef struct s_token
{
	char			*cmd;
	t_redirect		redirect;
	struct s_token	*next;
}	t_token;

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

typedef struct s_tmp
{
	int		i;
	int		i2;
	char	c;
	t_list	*lst;
	void	*tmp;
	char	path[PATH_MAX];
	char	**tab;
	char	*str;
	void	*ptr;
	char	home[PATH_MAX];
}	t_tmp;

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
t_list	*ft_wcfile(char *wc, char *path, char mode, char *add);
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

char	*ft_quajoin(char *s1, const char *s2, char *s3, const char *s4);

int		ft_strncmp2(const char *s1, const char *s2, size_t n);
int		ft_strrcmp2(const char *s1, const char *s2, size_t n);

char	*ft_chdir(char *line);
char	*ft_ecrase_q(char *word);

int		ft_isprohibited(char *line);
char	*ft_cutoff(char *str, size_t start, size_t len);
t_redirect	ft_redirect(char *line);
t_list	*ft_sort_word(t_list *lst);
char	**ft_list_to_tab(t_list *lst);

t_list	*ft_tab_to_list(char **tab, t_list *lst);
int		ft_wc_in_fw(char *line);
int		ft_next_word(char *line, size_t i);
char	*ft_add_q_dollar(char *line);
int		ft_next_cmd(char *line, size_t i);

t_token	*ft_tokennew(char *newcmd);

char *tokenize(char *line);
char **parsing(char *input);

#endif
