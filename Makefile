# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 16:02:49 by ttaquet           #+#    #+#              #
#    Updated: 2024/06/25 16:37:59 by bchedru          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minicheh

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

FILES = main

SRC_FILES = $(addprefix src/ $(FILES))

OBJ_DIR = obj/

SRCS = $(addsuffix .c, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

.PHONY = all clean fclean re

all: $(OBJ_DIR) $(OBJS)
	@echo "\033[32m✔ Compilation des fichiers objets...\033[37m"
	@ar -rcs $(NAME) $(OBJS)
	@echo "\033[32m✔ Lib créee.\033[37m"

clean:
	@echo "\033[32m✔ Suppression des fichiers objets...\033[37m"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

obj/%.o: src/*/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@
