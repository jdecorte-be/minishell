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
	struct s_token	*sup_token;
	struct s_token	*sub_token;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char				*line;
	struct s_redirect	redirect;
	struct s_cmd		*sup_cmd;
	struct s_cmd		*sub_cmd;
	struct s_cmd		*back;
	struct s_cmd		*and;
	struct s_cmd		*or;
}	t_cmd;

typedef struct s_data//  block de cmd  
{
	char	*line;// ls  //after prompt, without \32\32 space, "" or ''
	t_token	*token;
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

char	**ft_split2(char *str, char *set);
char	*ft_onespace(char *line);
char	*ft_epur_str(char *line);
int		ft_str_isspace(char *str);

void	ft_creat_tab2(char *str, size_t *end, char *set, int e);
void	ft_count_words2(char *str, size_t *i, char *set);
char	**ft_split3(char *str, char *set);

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
char	*ft_ecrase_p(char *line);

int		ft_isprohibited(char *line);
char	*ft_cutoff(char *str, size_t start, size_t len);
t_redirect	ft_redirect(char *line, t_redirect file, int e, int fd);
t_list	*ft_sort_word(t_list *lst);
char	**ft_list_to_tab(t_list *lst);

t_list	*ft_tab_to_list(char **tab, t_list *lst);
t_token	*ft_tab_to_token(char **tab);
t_token	*ft_tab_to_token2(char **tab, t_token *sup_token);
int		ft_wc_in_fw(char *line);
int		ft_next_word(char *line, size_t i);

char	*ft_add_q_dollar(char *line);

int		ft_next_cmd(char *line, size_t i);
char	*ft_cut_chevron(char *str);

t_redirect	ft_init_redirect(void);

t_token	*ft_tokennew(char *newcmd);
t_token	*ft_sub_tokennew(char *newcmd, t_token *sup);
t_token	*ft_tokenlast(t_token *token);
void	ft_tokenadd_back(t_token **atoken, t_token *new);

int		ft_strstrchr(char *str, char *set);

void	ft_skip_p(char *str, size_t *i);
void	ft_skip_q(char *str, size_t *i);

t_token	*ft_parsing(char *line);

char *tokenize(char *line);
char **parsing(char *input);

#endif
