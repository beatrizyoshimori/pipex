NAME = pipex
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT = ./libft/libft.a

SRCS = pipex.c \
	path_functions.c \
	pipex_utils.c \
	commands_functions.c

OBJS = $(SRCS:%.c=%.o)

all: libft $(NAME)

libft:
	make -C ./libft

%.o:%.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	cc $(OBJS) $(LIBFT) -o $(NAME)

clean:
	make clean -C ./libft 
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re libft