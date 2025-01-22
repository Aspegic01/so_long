# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 22:05:19 by mlabrirh          #+#    #+#              #
#    Updated: 2025/01/21 17:30:17 by mlabrirh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so.a

SRCS = main.c render.c map_validation.c player.c utils.c utils1.c utils2.c get_next_line.c get_next_line_utils.c ft_itoa.c animation_player.c utils3.c
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
