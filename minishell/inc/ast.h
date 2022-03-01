#ifndef AST_H
# define AST_H

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	int 			type;
	char			*cmd;
}	t_ast;

#endif