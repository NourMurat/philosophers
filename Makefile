# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 14:51:24 by numussan          #+#    #+#              #
#    Updated: 2022/11/22 21:15:04 by numussan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

SRCS		= philosophers.c utils.c start.c actions.c

OBJS		= $(SRCS:.c=.o)

CCF			= gcc -Wall -Wextra -Werror -g #-fsanitize=thread

RM			= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CCF) $(SRCS) -o $(NAME)

%.o: %.c philosophers.h
	$(CCF) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re