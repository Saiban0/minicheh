NAME = minishell

LIBAMOA = libamoa/libamoa.a

CC = cc

CFLAGS =	-Wall -Wextra -Werror -g \
			-Iinclude

LFLAGS =	-Llibamoa \
			-lamoa


BUILTINS =

MAIN = main

FILES = $(BUILTINS) \
$(MAIN)

SRC_FILES = $(addprefix src/BUILTINS/, $(BUILTINS)) \
$(addprefix src/MAIN/, $(MAIN))

OBJ_DIR = obj/

SRCS = $(addsuffix .c, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

bonus: $(NAME_BONUS)

clean :
	rm -rf $(OBJ_DIR)
	make fclean -C libamoa

fclean : clean
	rm -rf $(NAME)
	make fclean -C libamoa

re: fclean all

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBAMOA)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

$(LIBAMOA):
	make -C libamoa

$(OBJ_DIR):
	mkdir $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re bonus