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

void	move_player(t_data *data, int new_x, int new_y)
{
	data->map[data->player_y][data->player_x] = '0';
	data->count_move++;
	data->player_x = new_x;
	data->player_y = new_y;
	data->map[data->player_y][data->player_x] = 'P';
}

int	is_valid_move(t_data *data, int x, int y)
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

void	animation_file(int keycode, t_data *data)
{
	int	width;
	int	height;

	if (keycode == 119)
	{
		data->img_player[0] = mlx_xpm_file_to_image(data->mlx, "../sprites/Pac-Man/pac_closed.xpm", &width, &height); 
		data->img_player[1] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_semi_up.xpm", &width, &height); 
		data->img_player[2] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_open_up.xpm", &width, &height); 	
	}
	else if (keycode == 115)
	{

		data->img_player[0] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_closed.xpm", &width, &height); 
		data->img_player[1] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_semi_down.xpm", &width, &height); 
		data->img_player[2] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_open_down.xpm", &width, &height); 
	}
	else if (keycode == 97)
	{

		data->img_player[0] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_closed.xpm", &width, &height); 
		data->img_player[1] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_semi_left.xpm", &width, &height); 
		data->img_player[2] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_open_left.xpm", &width, &height); 		
	}
	else if (keycode == 100)
	{

		data->img_player[0] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_closed.xpm", &width, &height); 
		data->img_player[1] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_semi_right.xpm", &width, &height); 
		data->img_player[2] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_open_right.xpm", &width, &height); 
	}
}

int handle_keypress(int keycode, t_data *data)
{
	int new_x;
	int	new_y;
	int	width;
	int	height;

	new_x = data->player_x;
	new_y = data->player_y;
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 119)
	{
	new_y--;
	animation_file(119, data);
}
	else if (keycode == 115)
	{
		new_y++;
		animation_file(115, data);
	}
	else if (keycode == 97)
	{
		new_x--;
		animation_file(97, data);
	}
	else if (keycode == 100)
	{
		new_x++;
		animation_file(100, data);
	}
	if (is_valid_move(data, new_x, new_y))
	{
		int old_x = data->player_x;
		int	old_y = data->player_y;
		process_interaction(data, new_x, new_y);
		render_map(data);
	}
	return (0);
}
int	animation_loop(t_data *data)
{
	data->frame_count++;

	if (data->frame_count >= 30)
	{
		data->player_frame = (data->player_frame + 1) % 3;
		data->killer_frame = (data->killer_frame + 1) % 3;
		data->frame_count = 0;
	}
	render_map(data);
	return 0;
}

int keypress_handler(int keycode, t_data *data)
{
	data->keypress = keycode;
	return (0);
}
