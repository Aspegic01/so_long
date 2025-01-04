/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:13:53 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/01 22:14:01 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

void move_player(t_data *data, int new_x, int new_y)
{
	data->map[data->player_y][data->player_x] = '0';
	data->count_move++;
	data->player_x = new_x;
	data->player_y = new_y;
	data->map[data->player_y][data->player_x] = 'P';
}

int is_valid_move(t_data *data, int x, int y)
{
	char	tile;

	if (x < 0 || y < 0 || x >= data->cols || y >= data->rows)
		return (0);
	tile = data->map[y][x];
	return (tile == '0' || tile == 'C' || tile == 'E' || tile == 'T');
}

void process_interaction(t_data *data, int x, int y)
{
	char tile;

	tile = data->map[y][x];
	if (tile == 'C')
	{
		data->collect--;
		data->map[y][x] = '0';
	}
	else if (tile == 'E')
	{
		if (data->collect == 0)
		{
			move_player(data, x, y);
			close_window(data);
		}
		return;
	}
	else if (tile == 'T')
	{
		move_player(data, x, y);
		close_window(data);
	}

	move_player(data, x, y);
}

int handle_keypress(int keycode, t_data *data)
{
	int new_x;
	int	new_y;

	new_x = data->player_x;
	new_y = data->player_y;
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 119)
		new_y--;
	else if (keycode == 115)
		new_y++;
	else if (keycode == 97)
		new_x--;
	else if (keycode == 100)
		new_x++;

	if (is_valid_move(data, new_x, new_y))
	{
		process_interaction(data, new_x, new_y);
		mlx_clear_window(data->mlx, data->win);
		render_map(data);
	}
	return (0);
}
