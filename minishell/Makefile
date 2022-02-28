NAME 		=	minishell

CC 			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

FILES 		=	main.c

SRC_DIR		=	./src/
INC_DIR		=	./inc

SRCS		=	$(addprefix $(SRC_DIR), $(FILES))
OBJS		=	$(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) -o $@ $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all