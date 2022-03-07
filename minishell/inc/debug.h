#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "parse_user_input.h"

void	debug_print_vector(char **vector);
void	debug_print_tokens(t_token *tokens);
void	debug_print_t(t_ast_node *tree);

#endif
