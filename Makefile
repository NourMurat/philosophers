# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 14:51:24 by numussan          #+#    #+#              #
#    Updated: 2022/11/09 15:06:50 by numussan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philosophers

SRCS		= philosophers.c

OBJS		= $(SRCS:.c=.o)

CCF			= gcc -Wall -Wextra -Werror

MAKELIBFT	= cd libft && make

LIBFT		= libft/libft.a

RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKELIBFT)
	$(CCF) -o $(NAME) $(SRCS) $(LIBFT)

%.o: %.c philosophers.h
	$(CCF) -c $< -o $@
	
clean:
	$(RM) $(OBJS)
	$(MAKELIBFT) clean

fclean:
	$(RM) $(NAME)
	$(MAKELIBFT) fclean

re:
	fclean all

.PHONY: all clean fclean re libft