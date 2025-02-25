CC = cc

CFLAGS = -Wall -Wextra -Werror

PRINTF_DIR = printf

OBJ_DIR = obj

SRC = src/free.c src/ft_split.c src/ft_putstr_fd.c src/ft_split1.c src/get_commands.c src/get_paths.c src/init.c src/pipex.c src/utils.c

OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

PRINTF_OBJ = $(PRINTF_DIR)/libftprintf.a

NAME = pipex

$(NAME): $(OBJ) $(PRINTF_OBJ)
	${CC} ${CFLAGS} $(OBJ) $(PRINTF_OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

printf/libftprintf.a:
	$(MAKE) -C $(PRINTF_DIR)

all: $(NAME)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	${CC} ${CFLAGS} -c $< -o $@

#.c.o:
#	${CC} ${CFLAGS} -c  $< -o ${<:.c=.o}

clean: 
	rm -rf $(OBJ_DIR) 
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all