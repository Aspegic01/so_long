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
NAME = so_long.a
FLAGS = -lmlx -lX11 -lXext -lm
NAME_PROGRAMME = so_long
SRCS = main.c render.c map_validation.c player.c utils.c utils1.c utils2.c get_next_line.c get_next_line_utils.c ft_itoa.c animation_player.c utils3.c
OFILES = $(SRCS:.c=.o)

all: $(NAME_PROGRAMME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

$(NAME_PROGRAMME): $(NAME)
	$(CC) -o $(NAME_PROGRAMME) $(NAME) $(FLAGS)
	rm -rf $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(NAME) $(NAME_PROGRAMME)

re: fclean all

.PHONY: clean fclean re
.SECONDARY: $(OFILES) $(NAME)
