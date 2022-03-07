NAME 		=	minishell

CC 			=	gcc
CFLAGS		=	
READLINE	=	-L/usr/local/opt/readline/lib -lreadline -I/usr/local/opt/readline/include

RM			=	rm -f

FILES 		=	main.c \
				parse_user_input/parse_user_input.c \
				parse_user_input/mvs_split_utils.c \
				parse_user_input/mvs_split.c \
				parse_user_input/lexer.c \
				parse_user_input/parser.c \
				parse_user_input/parser_funcs.c \
				parse_user_input/parser_utils.c \
				parse_user_input/parser_utils_2.c \
				parse_user_input/tree_utils.c \
				builtin/cd.c \
				builtin/echo.c \
				builtin/env.c \
				builtin/exit.c \
				builtin/export_append.c \
				builtin/export.c \
				builtin/pwd.c \
				builtin/unset.c \
				utils/list_1.c \
				utils/list_2.c \
				utils/utils_1.c \
				utils/utils_2.c \
				utils/utils_3.c \
				our_env.c \
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