#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# include "parse_user_input.h"
# include "debug.h"

# define SPACE ' '
# define SQUOTE '\''
# define DQUOTE '\"'

# define MALLOC_ERROR 1

# define INFILE 0
# define OUTFILE 1

typedef enum e_redir
{
	IN_REDIR,
	IN_HEREDOC,
	OUT_REDIR,
	OUT_APPEND
}	t_redir;

typedef enum e_open
{
	READ,
	WRITE,
	APPEND
}	t_open;

typedef enum e_builtins
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET,
	NONE
}	t_builtins;

typedef enum e_status
{
	SUCCESS,
	FAILURE,
	MALLOC_ERR
}	t_stat;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*line;
}	t_list;

typedef struct s_necessities
{
	int		exit_status;
	int		pipe[2];
	int 	fd[2];
	int 	prev_dir;
	bool	pipeexists;
	char	*remainder;
	char	*fullpath;
	t_list	*env;
}	t_info;

/* envp friends */
t_list	*envp_to_ours(char **envp);
char	*get_value(t_list *env, char *key);
int		append_to_env(t_list *env, char *str);
char	**to_vector(t_list *env);
/* builtins */
int		mvs_echo(char **chunk, t_list *env);
int		mvs_exit(char **chunk, t_list *env); // is whitespace func necessary? + dequote have to be removed after parsing done
int		mvs_cd(char **chunk, t_list *env); // error handling to be done
int		mvs_pwd(char **chunk, t_list *env);
int		mvs_env(char **chunk, t_list *env);
int		mvs_export(char **chunk, t_list *env);
int		mvs_unset(char **chunk, t_list *env);
int		classify_builtin(char *str);
void	builtins_init(int (*func[])(char **, t_list *));

/* utils */
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_print_error(char *cmd, char *arg, char *error);
int		ft_free_str(char *str);
void	ft_free_vector(char **vector);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	dequote(char *str);
char	**ft_split(char const *s, char c);

/* list */
t_list	*ft_lstnew(char *line);
t_list	*ft_lstlast(t_list *lst);
t_list	*copy_list(t_list *src);
t_list	*sort_list(t_list *lst, int (*cmp)(const char *, const char *, size_t));
void	ft_printlist(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	delete_node(t_list *lst);
void	*ft_free_lst(t_list *lst);
size_t	ft_lstsize(t_list *lst);

/* exec */
int		keep_stdio(int *origin);
int		restore_stdio(int *origin);
int		lets_pipe(t_info *info);
int		here_doc(int infile, char *limiter);
int		builtin_or_not(char *content, t_info *info);
int		mvs_open(char *file, int mode);
int		teach_me_direction(char *content, t_info *info);
int		redir_n_join_remainder(char *content, t_info *info);
int		get_fullpath(char **content, t_info *info);

/* ?????? */
void run_tokens(t_ast_node *node, t_list *env, int *exit_status);

#endif