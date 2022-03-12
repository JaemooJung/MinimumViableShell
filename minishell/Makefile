NAME 		=	minishell

CC 			=	gcc
CFLAGS		=	-g
#READLINE	=	-L/usr/local/opt/readline/lib -lreadline -I/usr/local/opt/readline/include
READLINE	=	-L/opt/homebrew/opt/readline/lib -lreadline -I/opt/homebrew/opt/readline/include
RM			=	rm -f

FILES 		=	main.c \
				parse_user_input/parse_user_input.c \
				parse_user_input/split_input.c \
				parse_user_input/mvs_split.c \
				parse_user_input/mvs_split_utils.c \
				parse_user_input/lexer.c \
				parse_user_input/parser.c \
				parse_user_input/parser_funcs.c \
				parse_user_input/parser_utils.c \
				parse_user_input/parser_utils_2.c \
				parse_user_input/tree_utils.c \
				parse_user_input/expand_env.c \
				builtin/cd.c \
				builtin/echo.c \
				builtin/env.c \
				builtin/exit.c \
				builtin/export_append.c \
				builtin/export.c \
				builtin/pwd.c \
				builtin/unset.c \
				utils/ft_split.c \
				utils/list_1.c \
				utils/list_2.c \
				utils/utils_1.c \
				utils/utils_2.c \
				utils/utils_3.c \
				utils/utils_4.c \
				our_env.c \
				exec/run_tokens.c \
                exec/redir.c \
                exec/redir_utils.c \
                exec/execute.c \
                exec/pipe_n_dup.c \
                exec/path.c \
				debug/debug_print.c \

SRC_DIR		=	./src/
INC_DIR		=	./inc

SRCS		=	$(addprefix $(SRC_DIR), $(FILES))
OBJS		=	$(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(READLINE) -o $@ $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all
