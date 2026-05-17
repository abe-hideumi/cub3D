NAME = cub3D

SRCS =	main.c\
		srcs/free.c\

DISPLAY_SRCS =	display/init.c \
				display/hooks.c \
				display/render.c \
				display/rotate_calculations.c\
				display/render_utils.c \
				display/mock_config.c

OBJS = $(SRCS:.c=.o) $(DISPLAY_SRCS:.c=.o)

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
	MINILIBX_DIR = minilibx_mms_20200219
	MINILIBX_A = $(MINILIBX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

INCLUDES = -I. -Idisplay -Ilibft -I$(MINILIBX_DIR)

# colors for output
YELLOW = \033[1;33m
RED = \033[1;31m
GREEN = \033[1;32m
RESET = \033[0m

# rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX_A)
	@echo "$(GREEN)Linking cub3D executable...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft $(MLX_FLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft all

$(MINILIBX_A):
	$(MAKE) -C $(MINILIBX_DIR)

norm:
	@output=$$(norminette $(SRCS) $(DISPLAY_SRCS) display/*.h libft/*.c cub3D.h map.h parse_map.c); \
	if echo "$$output" | grep -q "Error"; then \
		echo "$$output" | grep "Error"; \
	else \
		echo "$(GREEN)Norminette: complete$(RESET)"; \
	fi

clean:
	@echo "$(YELLOW)Removing cub3D object files...$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) -C libft clean
	@$(MAKE) -C $(MINILIBX_DIR) clean

fclean:
	@echo "$(RED)Removing cub3D executable...$(RESET)"
	@rm -f $(OBJS) $(NAME)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C $(MINILIBX_DIR) clean

re: fclean all

.PHONY: all clean fclean re norm
