/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:02:10 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/22 03:00:02 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <strings.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <crt_externs.h>
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
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include <malloc/malloc.h>
// #include "wraloc.h"

typedef struct s_hd
{
	int			fd;
	struct s_hd	*next;
}				t_hd;

typedef struct s_redirect
{
	t_list	*infile;
	t_list	*outfile;
	int		infd;
	int		outfd;
	t_hd	*open;
	t_hd	*open2;
}				t_redirect;

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

typedef struct s_data
{
	int				offset;
	int				stophere;
	char			**env;
	int				lastret;
	int				stdin_reset;
	int				stdout_reset;
	int				inredirrs;
	int				outredirrs;
	int				is_redir_in;
	int				is_redir_out;
	int				stdin;
	int				stdout;
	int				is_subshell;
	int				is_pipe;
	int				pipe[2];
	t_token			*token;
	t_hd			*hd;
	struct termios	old;
	struct termios	new;
	int				hd_stop;
}	t_data;

typedef struct s_tmp
{
	size_t		i;
	size_t		i2;
	char		c;
	t_list		*lst;
	size_t		start;
	size_t		end;
	t_redirect	redirect;
	t_hd		hd;
	long		lend;
	long		lstart;
	long		lcount;
	void		*home2;
	void		*tmp;
	char		path[PATH_MAX];
	char		**tab;
	char		*str;
	void		*ptr;
	char		home[PATH_MAX];
	int			par;
	char		*temp;
	int			off;
	size_t		len;
	int			e_len;
}	t_tmp;

t_data	*g_data;

void		here_doc_sig1(int sig);
void		here_doc_sig2(int sig);

void		puterror(char *cmd, char *msg);
int			my_setenv2(char *var);
void		format_env(char *var);
char		*findenv(char *name, int *offset);
char		*get_path(char *cmd);
int			pipex(char *cmd);
char		*prompt(void);
char		*my_getenv(char *name, int *index);
int			my_setenv(char *name);
void		refresh_env(char **env, t_data *data);
int			checkvalid(char *cmd);
int			echo(char **args);
int			pwd(void);
int			cd(char **cmd);
int			export(char **cmd);
int			egal_len(char *cmd);
int			unset(char **cmd);
void		printlist(t_token *head);

t_list		*list_env(char **env);
char		**listtotab(t_list *lst);
void		env_cmd(t_data *data);
void		*ft_memdel(void *ptr);
void		replace_env(char *cmd, t_list *env);

void		*ft_realloc(void *str, size_t len);

int			first_pipe(t_data *d_env, char *cmd);
int			last_pipe(char *cmd);
int			mid_pipe(char *cmd);
void		ft_clean_hd(t_hd *hd);

int			subshell(char *line);
void		addspace(char **str);
char		**ft_split2(char *str, char *set);
char		*ft_onespace(char *line);

t_data		*ft_datanew(char	*line);
t_data		*ft_datalast(t_data *data);
void		ft_dataadd_back(t_data **data, t_data *new);

char		**ft_split2(char *str, char *set);
char		*ft_onespace(char *line);
char		*ft_epur_str(char *line);
int			ft_str_isspace(char *str);
void		ft_error(int e);

int			ft_free(char *line);
void		*ft_memdel(void *ptr);
int			run_cmd(t_data *d_env, char *cmd);
int			cmdlexer(char *cmd, t_data *d_env);

char		**sort_exp(char **env);

char		*tokenize(char *line);
char		*ft_pgross_str(char *line);
char		*ft_epur_str(char *line);
void		execute(t_token *token);

t_cmd		*ft_cmdlast(t_cmd *cmd);
void		ft_cmdadd_back(t_cmd **cmd, t_cmd *new);

char		**ft_split2(char *str, char *set);
char		*ft_onespace(char *line);
char		*ft_epur_str(char *line);
int			ft_str_isspace(char *str);

void		ft_creat_tab2(char *str, size_t *end, char *set, int e);
void		ft_count_words2(char *str, size_t *i, char *set);
char		**ft_split3(char *str, char *set);

t_cmd		*ft_creat_cmd(char *line);
char		*ft_pgross_str(char *line);
char		*ft_chdollar(char *line);

char		**ft_split4(char *str, char *set);
char		*ft_chwc(char *line);
t_list		*ft_wcfile(char *wc, char *path, char mode, char *add);
t_list		*ft_wcsearch(char *line);

char		*ft_trijoin(char *s1, char *s2, char *s3, int e);
int			ft_exist(char *str, size_t len);
char		*ft_lstmerge(t_list *lst);
char		*ft_woquote(char *line);
char		*ft_replace(char *str, char *search, char *replace);

void		ft_error(int e);
int			ft_free(char *line);
void		ft_free_tab(char **tab);

char		*tokenize(char *line);
char		*ft_strjoin1(char const *s1, char const *s2);
char		*ft_strjoin2(char const *s1, char const *s2);
char		*ft_strjoin3(char const *s1, char const *s2);
int			pipe_handler(t_data *d_env, char **input, int *i);
void		*ft_memdel(void *ptr);
int			pipe_is_after(char **input, int i);
int			exec(char *cmd);
char		**sort_exp(char **env);

char		*tokenize(char *line);
char		*ft_pgross_str(char *line);
char		*ft_epur_str(char *line);
char		*ft_strjoin2(char const *s1, char const *s2);

char		*ft_quajoin(char *s1, char *s2, char *s3, char *s4);
char		*ft_ecrase_q(char *word);
int			ft_strncmp2(const char *s1, const char *s2, size_t n);
int			ft_strrcmp2(const char *s1, const char *s2, size_t n);
int			print_env(char **env);
void		print_exp(t_data *data);
int			splitlen(char **split);
char		*ft_chdir(char *line);
int			what_im(char *input);
void		exit_cmd(char **s_cmd);
int			cmd_sys(char *cmd);
void		ft_redirect_for_john(t_token *token);
char		*ft_ecrase_q(char *word);
char		*ft_ecrase_p(char *line);

int			ft_isprohibited(char *line);
char		*ft_cutoff(char *str, size_t start, size_t len);
t_redirect	ft_redirect(char *line, t_redirect file, int e, int fd);
t_list		*ft_sort_word(t_list *lst);
char		**ft_list_to_tab(t_list *lst);

t_list		*ft_tab_to_list(char **tab, t_list *lst);
t_token		*ft_tab_to_token(char **tab);
t_token		*ft_tab_to_token2(char **tab, t_token *sup_token);
int			ft_wc_in_fw(char *line);
int			ft_next_word(char *line, size_t i);

char		*ft_add_q_dollar(char *line);

int			ft_next_cmd(char *line, size_t i);
char		*ft_cut_chevron(char *str);

t_redirect	ft_init_redirect(void);

t_token		*ft_tokennew(char *newcmd);
t_token		*ft_sub_tokennew(char *newcmd, t_token *sup);
t_token		*ft_tokenlast(t_token *token);
void		ft_tokenadd_back(t_token **atoken, t_token *new);
t_token		*ft_parsing(char *line);
char		*ft_ecrase_q(char *word);
char		*ft_ecrase_p(char *line);

t_token		*ft_token_next(t_token *token);
void		ft_token_free_and_next(t_token **token);
void		ft_token_free_and_sup(t_token **token);
void		ft_tokenclean_all(t_token **token);

int			ft_strstrchr(char *str, char *set);

void		ft_skip_p(char *str, size_t *i);
void		ft_skip_q(char *str, size_t *i);

t_token		*ft_parsing(char *line);

char		*ft_redirect_chwc(char *line);
int			ft_chwc_ok2(char *line);
char		*ft_transf(char *line);
int			ft_hd_exist(char *line);
int			ft_here_doc(char *line);

char		*ft_purge_q(char *line);
int			pipex2(char *cmd);

t_hd		*ft_hd_finder(char *line);

t_hd		*ft_hdnew(int fd);
t_hd		*ft_hdlast(t_hd *hd);
void		ft_hdadd_back(t_hd **hd, t_hd *new);
int			ft_hdsize(t_hd *hd);

int			*ft_hd_to_tab(t_hd *hd);
t_hd		*ft_sort_hd(t_hd *hd, char *line, t_token *token);
char		*ft_chdollar_hd(char *line);
void		ft_skip_hd(char *line);

char		*tokenize(char *line);
char		**parsing(char *input);
char		*ft_chwc_str(char *line, t_list *name, t_list *wc, t_list *woq);

void		c_handler(int sig);
void		c_handler_fork(int sig);
void		q_handler_fork(int sig);
void		c_handler_doc(int sig);

void		ft_exit(int numerror);

char		**array_dup(char **tab);

void		init(int *start, int *is_and, int *is_or, int *is_ope);
void		init_2(t_token *tmp);

void		redirect_exec(t_token *token, int mode);

#endif
