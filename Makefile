# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 22:05:19 by mlabrirh          #+#    #+#              #
#    Updated: 2025/01/01 22:05:48 by mlabrirh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long.a

SRCS = main.c rander.c map_validation.c player.c utils.c utils1.c get_next_line.c get_next_line_utils.c ft_itoa.c
OFILES =	$(SRCS:.c=.o)

$(NAME): $(OFILES)

all: $(NAME)

%.o: %.c 
	$(CC) -c $(FLAGS) $< -o $@
	ar rcs $(NAME) $@

clean:
	rm -rf  $(OFILES) 

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY:	clean
.SECONDARY: $(OFILES)
