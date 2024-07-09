NAME = minishell

LIBAMOA = libamoa/libamoa.a

CC = cc

CFLAGS =	-Wall -Wextra -Werror -g \
			-IInclude 

LFLAGS =	-Llibamoa \
			-lamoa

BUILTINS =

EXECUTING = exec_simple exec_utils

MAIN = main

PARSE = parse_utils parse parsing_test pipe_handler redirect_handler

FILES = $(BUILTINS) \
$(EXECUTING) \
$(MAIN) \
$(PARSE)

SRC_FILES = $(addprefix src/BUILTINS/, $(BUILTINS)) \
$(addprefix src/EXECUTING/, $(EXECUTING)) \
$(addprefix src/MAIN/, $(MAIN)) \
$(addprefix src/PARSE/, $(PARSE))

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