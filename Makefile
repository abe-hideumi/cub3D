NAME = cub3D

SRCS =	main.c \

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

# detect OS
UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	MINILIBX_DIR = minilibx-linux
	MINILIBX_A = $(MINILIBX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MINILIBX_DIR) -lmlx -lX11 -lXext -lm
else
	MINILIBX_DIR = minilibx-macos
	MINILIBX_A = $(MINILIBX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

INCLUDES = -I. -Ilibft -I$(MINILIBX_DIR)

# colors for output
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

# rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX_A)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft all

$(MINILIBX_A):
	$(MAKE) -C $(MINILIBX_DIR)

clean:
	@echo "$(YELLOW)Removing object files...$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) -C libft clean
	@$(MAKE) -C $(MINILIBX_DIR) clean

fclean:
	@echo "$(RED)Removing executable...$(RESET)"
	@rm -f $(OBJS) $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
