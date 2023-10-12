CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRCS = ft_printf.c ft_putnbr.c ft_itoaprintf.c ft_printf_utils.c ft_putstr.c ft_puthex.c ft_putptr.c ft_typefinder.c ft_putunsigned.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

clean:
		rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all
