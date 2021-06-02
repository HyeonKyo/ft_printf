# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/02 15:43:53 by hyeonkki          #+#    #+#              #
#    Updated: 2021/06/02 15:43:54 by hyeonkki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
