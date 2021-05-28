CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = .
OBJS = $(SRCS:.c=.o)
AR = ar -rc
NAME = libftprintf.a
RM = rm -f

all		:	$(NAME)

$(NAME)	:	$(OBJS_FILES)
			$(AR) $(NAME) $^

clean	:
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

bonus	:

.PHONY	:	all clean fclean re bonus