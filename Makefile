NAME = cub3D

SRCS =	main.c \
		free.c

PARSE_SRCS =	parse/parse_cub_file.c \
				parse/parse_texture.c \
				parse/parse_cub_utils.c \
				parse/read_file.c \
				parse/validate_map_chars.c \
				parse/validate_map_enclosed.c

DISPLAY_SRCS =	display/init.c \
				display/hooks.c \
				display/handle_move_utils.c \
				display/rotate_calculations.c\
				display/put_color.c \
				display/render.c \
				display/init_ray.c\
				display/cleanup.c

OBJS = $(SRCS:.c=.o) $(DISPLAY_SRCS:.c=.o) $(PARSE_SRCS:.c=.o)

HEADERS = display/display.h parse/map.h

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

LIBFT = libft/libft.a

# detect OS
UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	MINILIBX_DIR = minilibx-linux
	MINILIBX_A = $(MINILIBX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MINILIBX_DIR) -lmlx -lX11 -lXext -lm
else
	MINILIBX_DIR = minilibx_opengl_20191021
	MINILIBX_A = $(MINILIBX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

INCLUDES = -Ilibft -Ilibft/get_next_line -I$(MINILIBX_DIR)

# colors for output
YELLOW = \033[1;33m
RED = \033[1;31m
GREEN = \033[1;32m
RESET = \033[0m

# rules
all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX_A) $(OBJS)
	@echo "$(GREEN)Linking cub3D executable...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft $(MLX_FLAGS)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft all

$(MINILIBX_A):
	$(MAKE) -C $(MINILIBX_DIR)

norm:
	@output=$$(norminette $(SRCS) $(DISPLAY_SRCS) $(PARSE_SRCS) $(HEADERS)); \
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
