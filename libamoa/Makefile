# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 16:02:49 by ttaquet           #+#    #+#              #
#    Updated: 2024/06/25 20:20:40 by bchedru          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libamoa.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

CTYPE = ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_tolower ft_toupper

DOUBLE_ARRAY = double_array_size ft_free_double_array ft_print_double_array

GET_NEXT_LINE = get_next_line

IO = ft_putchar_fd ft_putendl_fd ft_putnbr_base_fd ft_putnbr_fd ft_putstr_fd

LINKED_LIST = ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone ft_lstiter \
ft_lstlast ft_lstmap ft_lstnew ft_lstsize

PRINTF = ft_printf_utils ft_printf

STDLIB = ft_abs ft_atoi ft_atol ft_calloc

STRING = ft_bzero ft_intlen ft_itoa ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset \
ft_split ft_strchr ft_strcmp ft_strcpy ft_strdup ft_striteri ft_strjoin ft_strlcat ft_strlcpy \
ft_strlen ft_strmapi ft_strncmp ft_strnstr ft_strrchr ft_strtrim ft_substr ft_swap

FILES = $(CTYPE) \
$(DOUBLE_ARRAY) \
$(GET_NEXT_LINE) \
$(IO) \
$(LINKED_LIST) \
$(PRINTF) \
$(STDLIB) \
$(STRING)

SRC_FILES = $(addprefix src/CTYPE/, $(CTYPE)) \
$(addprefix src/DOUBLE_ARRAY/, $(DOUBLE_ARRAY)) \
$(addprefix src/GET_NEXT_LINE/, $(GET_NEXT_LINE)) \
$(addprefix src/IO/, $(IO)) \
$(addprefix src/LINKED_LIST/, $(LINKED_LIST)) \
$(addprefix src/PRINTF/, $(PRINTF)) \
$(addprefix src/STDLIB/, $(STDLIB)) \
$(addprefix src/STRING/, $(STRING))

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
