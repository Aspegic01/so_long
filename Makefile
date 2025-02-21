# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 16:33:04 by mlabrirh          #+#    #+#              #
#    Updated: 2025/01/27 16:38:06 by mlabrirh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME1 = so_long.a
NAME2 = so_long_bonus.a
FLAGS = -lmlx -lX11 -lXext -lm
NAME_PROGRAMME = so_long
NAME_PROGRAMME_BONUS = so_long_bonus
SRCS = ./Mandatory/main.c ./Mandatory/render.c ./Mandatory/map_validation.c ./Mandatory/player.c \
	   ./Mandatory/utils.c ./Mandatory/utils1.c ./Mandatory/utils2.c ./Mandatory/get_next_line.c \
	   ./Mandatory/get_next_line_utils.c ./Mandatory/ft_itoa.c ./Mandatory/utils3.c
BONUS = ./Bonus/main_bonus.c ./Bonus/render_bonus.c ./Bonus/map_validation_bonus.c ./Bonus/player_bonus.c \
		./Bonus/utils_bonus.c ./Bonus/utils1_bonus.c ./Bonus/utils2_bonus.c ./Bonus/get_next_line.c \
		./Bonus/get_next_line_utils.c ./Bonus/ft_itoa.c ./Bonus/animation_player_bonus.c ./Bonus/utils3_bonus.c
OFILES = $(SRCS:.c=.o)
BOFILES = $(BONUS:.c=.o)

all: $(NAME_PROGRAMME)

$(NAME1): $(OFILES)
	ar rcs $(NAME1) $(OFILES)

$(NAME_PROGRAMME): $(NAME1)
	$(CC) -o $(NAME_PROGRAMME) $(NAME1) $(FLAGS)
	rm -rf $(NAME1)

bonus: $(NAME_PROGRAMME_BONUS)

$(NAME2): $(BOFILES)
	ar rcs $(NAME2) $(BOFILES)

$(NAME_PROGRAMME_BONUS): $(NAME2)
	$(CC) -o $(NAME_PROGRAMME_BONUS) $(NAME2) $(FLAGS)
	rm -rf $(NAME2)

./mandatory/%.o: ./mandatory/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OFILES) $(BOFILES)

fclean: clean
	rm -rf $(NAME1) $(NAME2) $(NAME_PROGRAMME) $(NAME_PROGRAMME_BONUS)

re:	fclean all

.PHONY: clean fclean re bonus
.SECONDARY: $(OFILES) $(NAME1) $(BOFILES) $(NAME2)
