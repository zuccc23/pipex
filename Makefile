CC = cc

CFLAGS = -Wall -Wextra -Werror

PRINTF_DIR = printf

SRC = free.c ft_split.c ft_putstr_fd.c ft_split1.c get_commands.c get_paths.c init.c pipex.c utils.c

OBJ = $(SRC:.c=.o)

PRINTF_OBJ = $(PRINTF_DIR)/libftprintf.a

NAME = pipex

$(NAME): $(OBJ) $(PRINTF_OBJ)
	${CC} ${CFLAGS} $(OBJ) $(PRINTF_OBJ) -o $(NAME)

printf/libftprintf.a:
	$(MAKE) -C $(PRINTF_DIR)

all: $(NAME)

.c.o:
	${CC} ${CFLAGS} -c  $< -o ${<:.c=.o}

clean: 
	rm -rf $(OBJ) 
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all