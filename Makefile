SRC_PRINTF = ft_char.c ft_printf.c  ft_string.c \
			ft_hex_1.c ft_hex_2.c \
			ft_int_1.c ft_int_2.c \
			ft_unsigned_1.c ft_unsigned_2.c \
			ft_outils_1.c ft_outils_2.c \
			ft_outils_3.c ft_outils_4.c

CC	=	cc
CFLAGS = -Wall -Wextra -Werror -I.

OBJ_PRINTF = $(SRC_PRINTF:.c=.o)

NAME = libftprintf.a

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_PRINTF)
	ar rcv $@ $^

bonus: $(OBJ_PRINTF)
	ar rcv $(NAME) $^

clean:
	rm -rf $(OBJ_PRINTF)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
