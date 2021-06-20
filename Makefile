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

LIB_DIR = ./libft

SRCS_DIR = ./src
SRCS_NAME = ft_printf.c utils1.c utils2.c utils3.c find_opt.c get_opt.c\
	d_print1.c d_print2.c u_print1.c u_print2.c x_print1.c x_print2.c p_print.c\
	c_print1.c c_print2.c s_print1.c s_print2.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_NAME))

OBJS_NAME = $(SRCS:.c=.o)
OBJS = $(addprefix $(SRCS_DIR)/, $(OBJS_NAME))

INC = -I$(LIB_DIR) -I./include

BNS_DIR = ./bonus
BNS_NAME = n_print1.c n_print2.c

NAME = libftprintf.a

AR = ar -rc
RM = rm -rf

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(MAKE) -C $(LIB_DIR) bonus
			cp $(LIB_DIR)/libft.a $@
			$(AR) $@ $^

.c.o	:
			$(CC) $(CFLAGS) -c $(SRCS) $(INC)

clean	:
			$(RM) $(OBJS)
			$(MAKE) -C $(LIB_DIR) fclean

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

bonus	:	re

.PHONY	:	all clean fclean re bonus
