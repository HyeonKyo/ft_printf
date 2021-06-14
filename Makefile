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
SRCS = ft_printf.c utils1.c utils2.c utils3.c d_print.c u_print.c x_print.c \
	p_print.c c_print.c get_opt.c find_opt.c f_print1.c f_print2.c e_print.c\
	s_print.c
OBJS = $(SRCS:.c=.o)
AR = ar -rcs
NAME = libftprintf.a
LIB_DIR = ./libft
RM = rm -f

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(MAKE) -C $(LIB_DIR) bonus
			cp $(LIB_DIR)/libft.a $@
			$(AR) $@ $^

.c.o	:
			$(CC) $(CFLAGS) -c $(SRCS) -I./

clean	:
			$(RM) $(OBJS)
			$(MAKE) -C $(LIB_DIR) clean

fclean	:	clean
			$(RM) $(LIB_DIR)/libft.a
			$(RM) $(NAME)

re		:	fclean all

bonus	:	re

.PHONY	:	all clean fclean re bonus
