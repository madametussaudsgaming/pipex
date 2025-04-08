# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpadasia <rpadasia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 14:52:56 by rpadasia          #+#    #+#              #
#    Updated: 2025/04/08 19:28:25 by rpadasia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(HEADER_DIR)
RM = rm -rf

SRC = pipex.c executor.c
OBJ = $(SRC:.c=.o)

HEADER_DIR = include
OBJ_DIR = objs
OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(OBJ))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_PATH) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_PATH) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) all

clean:
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean -s

re: clear fclean all

.PHONY: all clean fclean re clear
