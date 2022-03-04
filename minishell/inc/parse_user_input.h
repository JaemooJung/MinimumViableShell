#ifndef AST_H
# define AST_H

# define T_NULL 1
# define T_PIPE 2
# define T_REDIRECTION 3
# define T_WORD 4

# define LEFT 0
# define RIGHT 1

typedef struct s_ast_node t_ast_node;

typedef struct s_token {
	int			type;
	char		*value;
}	t_token;

typedef struct s_ast_node
{
	t_token			*token;
	t_ast_node		*left;
	t_ast_node		*right;
}	t_ast_node;

bool	m_is_space(char c);
bool	m_is_quote(char c);
void	ft_free_split(char **splitted, int index);
char	**mvs_split(char const *s);

t_ast_node	*make_ast_node(t_token *token);
t_ast_node	*ast_insert(t_ast_node *root, t_token *token);

int		lexer(char **splitted, t_token **tokens);
int		parser(t_token **tokens, t_ast_node **tree);


int		parse_user_input(const char *input, t_ast_node **tree);

#endif