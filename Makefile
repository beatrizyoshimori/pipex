NAME = pipex
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT = ./libft/libft.a
BONUSLIB = ./bonus/libbonus.a

SRCS = mandatory/pipex.c \
	mandatory/path_functions.c \
	mandatory/pipex_utils.c \
	mandatory/commands_functions.c \
	mandatory/error.c

OBJS = $(SRCS:%.c=%.o)

BONUS_SRCS = bonus/pipex_bonus.c \
	bonus/path_functions_bonus.c \
	bonus/pipex_utils_bonus.c \
	bonus/commands_functions_bonus.c \
	bonus/pipe_functions_bonus.c \
	bonus/error_bonus.c

BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)

all: libft $(NAME)

libft:
	make -C ./libft

%.o:%.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	cc $(OBJS) $(LIBFT) -o $(NAME)

bonus: libft $(BONUSLIB)

$(BONUSLIB): $(BONUS_OBJS) $(LIBFT)
	ar rcs $(BONUSLIB) $(BONUS_OBJS)
	cc $(BONUSLIB) $(LIBFT) -o $(NAME)

clean:
	make clean -C ./libft 
	rm -f $(OBJS) $(BONUS_OBJS) $(BONUSLIB)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re libft bonus rebonus