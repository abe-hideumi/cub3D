
NAME = habe.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SRCS = init.c\
		hooks.c\
		render.c

OBJS = $(SRCS:.c=.o)

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	MINILIBX_DIR = ../minilibx-linux
	MLX_FLAGS = -L$(MINILIBX_DIR) -lmlx -lX11 -lXext -lm
else
	MINILIBX_DIR = ../minilibx_mms_20200219
	MLX_FLAGS = -L$(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

INCLUDES = -I. -I.. -I$(MINILIBX_DIR)

# colors for output
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(YELLOW)Removing habe object files...$(RESET)"
	@rm -f $(OBJS)

fclean:
	@echo "$(RED)Removing habe.a...$(RESET)"
	@rm -f $(OBJS)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
