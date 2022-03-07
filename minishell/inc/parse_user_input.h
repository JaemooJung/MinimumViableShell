#ifndef PARSE_USER_INPUT_H
# define PARSE_USER_INPUT_H

# define T_NULL 1
# define T_PIPE 2
# define T_REDIRECTION 3
# define T_WORD 4

# define NODE_PIPE 1
# define NODE_PHRASE 2
# define NODE_REDIRS 3
# define NODE_IO_REDIR 4
# define NODE_COMMAND 5
# define NODE_REDIR_TYPE 6
# define NODE_FILE_NAME 7
# define NODE_FILE_PATH 8
# define NODE_ARGV 9

# define LEFT 0
# define RIGHT 1

typedef struct s_ast_node	t_ast_node;

typedef struct s_token
{
	int			type;
	char		*value;
}	t_token;

typedef struct s_ast_node
{
	int				node_type;
	char			*content;
	t_ast_node		*left;
	t_ast_node		*right;
}	t_ast_node;

bool		m_is_space(char c);
bool		m_is_quote(char c);
void		ft_free_split(char **splitted, int index);
char		**mvs_split(char const *s);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
char		*conv_str_join(char *argv, char *new_str);
char		*make_argv(t_token **tokens);
void		print_parsed(t_ast_node *tree);

t_ast_node	*make_ast_node(int node_type, char *content);
t_ast_node	*ast_insert(t_ast_node *root, t_token *token, int side);
t_ast_node	*ast_insert_node(t_ast_node *root, t_ast_node *node, int side);

int			lexer(char **splitted, t_token **tokens);
int			parse_pipeline(t_ast_node **root, t_token **tokens);
int			parser(t_token **tokens, t_ast_node **tree);

int			parse_user_input(const char *input, t_ast_node **tree);

#endif