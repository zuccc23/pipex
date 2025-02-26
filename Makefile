CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj

SRC = src/free.c src/ft_split.c src/ft_putstr_fd.c src/ft_split1.c src/get_commands.c src/get_paths.c src/init.c src/pipex.c src/utils.c

OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

NAME = pipex

$(NAME): $(OBJ)
	${CC} ${CFLAGS} $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

all: $(NAME)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	${CC} ${CFLAGS} -c $< -o $@

clean: 
	rm -rf $(OBJ_DIR) 

fclean: clean
	rm -rf $(NAME)

re: fclean all