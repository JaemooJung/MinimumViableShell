#include "ast.h"

void pre_traverse(t_ast *node)
{
	exec_tree(node);
	if (node->left != NULL)
		pre_traverse(node->left);
	if (node->right != NULL)
		pre_traverse(node->right);
}

void exec_tree(t_ast *node)
{
  if 
}