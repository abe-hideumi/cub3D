
NAME = display.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SRCS = init.c\
		hooks.c\
		render.c\
		minimap_render.c

OBJS = $(SRCS:.c=.o)

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	MINILIBX_DIR = ../minilibx-linux
else
	MINILIBX_DIR = ../minilibx_mms_20200219
endif

INCLUDES = -I. -I.. -I$(MINILIBX_DIR)

# colors for output
YELLOW = \033[1;33m
RED = \033[1;31m
GREEN = \033[1;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling display library...$(RESET)"
	@$(AR) $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(YELLOW)Removing display object files...$(RESET)"
	@rm -f $(OBJS)

fclean:
	@echo "$(RED)Removing display library...$(RESET)"
	@rm -f $(OBJS)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
