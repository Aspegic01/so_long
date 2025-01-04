/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:58:00 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/01 21:58:07 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

//#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

typedef struct	s_data
{
    void	*mlx;
    void	*win;
    void	*img_empty;
    void	*img_wall;
    void	*img_collectible;
    void	*img_exit;
    void	*img_player;
    void	*img_killer;
    int		player_x;
    int		player_y;
    char	**map;
    int		rows;
    int		cols;
    int		collect;
	int		count_move;
}	t_data;

void	error_exit(const char *msg);
void	ft_putstr(char *msg);
char	*ft_itoa(int n);
int		validate_extension(const char *file, const char *ext);
void	count_collect(t_data *data);
int		compare_first_rows_with_other(char **map, int rows, int cols);
int		is_wall_consistent(char **map, int rows, int cols);
int		validate_map(char *map[], int rows, int cols);
void	rander_text(t_data*data);
void	put_image(t_data *data, char tile, int x, int y);
void	render_map(t_data *data);
void	move_player(t_data *data, int new_x, int new_y);
int		is_valid_move(t_data *data, int x, int y);
void	process_interaction(t_data *data, int x, int y);
int		handle_keypress(int keycode, t_data *data);
void	initialize_player_position(t_data *data);
int		is_path_to_exit(t_data data, char **map);
int		is_path_to_collect(t_data data, char **map);
int		close_window(t_data *data);
int		read_map(const char *file, t_data *data);

#endif
