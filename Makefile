NAME = cub3D

SRCS = 	main.c\

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft

$(LIBFT):
	make -C libft all

clean:
	@echo "$(YELLOW)Removing object files...$(RESET)"
	@rm -f $(OBJS)
	@make -C libft clean

fclean:
	@echo "$(RED)Removing executable...$(RESET)"
	@rm -f $(OBJS) $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
