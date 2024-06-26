NAME = minishell

LIBAMOA = libamoa/libamoa.a

CC = cc

CFLAGS =	-Wall -Wextra -Werror -g \
			-IInclude

LFLAGS =	-Llibamoa \
			-lamoa


BUILTINS =

MAIN = main

EXECUTING = exec_simple exec_utils

ERROR_MANAGEMENT = error_management

FILES = $(BUILTINS) \
$(MAIN) \
$(EXECUTING) \
$(ERROR_MANAGEMENT)

SRC_FILES = $(addprefix src/BUILTINS/, $(BUILTINS)) \
$(addprefix src/MAIN/, $(MAIN)) \
$(addprefix src/EXECUTING/, $(EXECUTING)) \
$(addprefix src/ERROR_MANAGEMENT/, $(ERROR_MANAGEMENT))

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

obj/%.o: src/*/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re