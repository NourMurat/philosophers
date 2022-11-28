# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 14:51:24 by numussan          #+#    #+#              #
#    Updated: 2022/11/28 17:07:55 by numussan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

.SILENT:

SRCS		= srcs/philosophers \
		srcs/parsing \
		srcs/utils \
		srcs/utils2 \
		srcs/start \
		srcs/actions

OBJDIR 		= objects

OBJS		= $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

CCF			= gcc -g -Wall -Wextra -Werror -fsanitize=thread

RM			= rm -rf

$(OBJDIR)/%.o: %.c srcs/philosophers.h
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/srcs
	$(CCF) -c $< -o $@

all: $(NAME)
	tput setaf 2
	printf "Executable"
	tput setaf 1
	printf " Provided 🤓\n";
	tput setaf 7
	printf "  .---------.\n";
	printf "  |.-------.|\n";
	printf "  ||>run   ||\n";
	printf "  ||       ||\n";
	printf "  |'-------'|\n";
	printf ".-^---------^-.\n";
	printf "| Philo start |\n";
	printf "'-------------'\n";

$(NAME): $(OBJS)
	@$(CCF) $(OBJS) -o $(NAME) -pthread

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re