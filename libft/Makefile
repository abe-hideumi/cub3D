# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 16:21:00 by habe              #+#    #+#              #
#    Updated: 2026/05/12 18:27:50 by habe             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_FILES = atoi\
			bzero\
			calloc\
			isalnum\
			isalpha\
			isascii\
			isdigit\
			isprint\
			itoa\
			memchr\
			memcmp\
			memcpy\
			memmove\
			memset\
			putchar_fd\
			putendl_fd\
			putnbr_fd\
			putstr_fd\
			split\
			strchr\
			strdup\
			striteri\
			strjoin\
			strlcat\
			strlcpy\
			strlen\
			strmapi\
			strncmp\
			strnstr\
			strrchr\
			strtrim\
			substr\
			tolower\
			toupper

BONUS_SRC_FILES = lstnew\
			lstadd_front\
			lstsize\
			lstlast\
			lstadd_back\
			lstdelone\
			lstclear\
			lstiter\
			lstmap

SRC = $(addprefix ft_, $(addsuffix .c, $(SRC_FILES)))
OBJ = $(SRC:.c=.o)

BONUS_SRC = $(addprefix ft_, $(addsuffix _bonus.c, $(BONUS_SRC_FILES)))
BONUS_OBJ = $(BONUS_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

RED = \033[1;31m
YELLOW = \033[1;33m
GREEN = \033[1;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Compiling libft library...$(RESET)"
	@ar rcs $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: .bonus

.bonus: $(OBJ) $(BONUS_OBJ)
	@echo "$(GREEN)Compiling libft bonus functions...$(RESET)"
	@ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
	@touch .bonus

clean:
	@echo "$(YELLOW)Removing libft object files...$(RESET)"
	@$(RM) $(OBJ) $(BONUS_OBJ) .bonus

fclean:
	@echo "$(RED)Removing libft library...$(RESET)"
	@$(RM) $(OBJ) $(BONUS_OBJ) .bonus
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
