/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:28:29 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/27 16:28:34 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	move_player(t_data *data, int new_x, int new_y)
{
	data->count_move++;
	data->map[data->player_y][data->player_x] = '0';
	data->player_x = new_x;
	data->player_y = new_y;
	data->map[data->player_y][data->player_x] = 'P';
}

char	is_valid_move(t_data *data, int x, int y)
{
	char	tile;

	if (x < 0 || y < 0 || x >= data->cols || y >= data->rows)
		return (0);
	tile = data->map[y][x];
	return (tile == '0' || tile == 'C' || tile == 'E' || tile == 'T');
}

void	process_interaction(t_data *data, int x, int y)
{
	char	tile;

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
		return ;
	}
	else if (tile == 'T')
	{
		move_player(data, x, y);
		close_window(data);
	}
	move_player(data, x, y);
}

void	handle_direction(int keycode, t_data *data, int *new_x, int *new_y)
{
	if (keycode == 119)
	{
		(*new_y)--;
		animation_file(119, data);
	}
	else if (keycode == 115)
	{
		(*new_y)++;
		animation_file(115, data);
	}
	else if (keycode == 97)
	{
		(*new_x)--;
		animation_file(97, data);
	}
	else if (keycode == 100)
	{
		(*new_x)++;
		animation_file(100, data);
	}
}

int	handle_keypress(int keycode, t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = data->player_x;
	new_y = data->player_y;
	if (keycode == 65307)
		close_window(data);
	else
	{
		handle_direction(keycode, data, &new_x, &new_y);
		if (is_valid_move(data, new_x, new_y))
		{
			process_interaction(data, new_x, new_y);
			render_map(data);
		}
	}
	return (0);
}
