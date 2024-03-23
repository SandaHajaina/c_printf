LIBC = ft_printf.c ft_print_hex.c ft_print_nbr.c ft_print_str.c

SRC = ${LIBC}

OBJ = ${SRC:.c=.o}

NAME = libftprintf.a

CC = gcc

CFLAGS = -Werror -Wextra -Wall

$(NAME) : ${OBJ}
		ar -rcs $@ ${OBJ}

all : ${NAME}

clean :
		rm -f ${OBJ}

fclean : clean
		rm -f ${NAME}

re : fclean all

.PHONY: all clean fclean re
