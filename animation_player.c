/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:47:40 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/21 17:39:48 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>

void	animation_player_up(t_data *data)
{
	int	width;
	int	height;

	data->img_player[0] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites//Pac-Man/pac_closed.xpm", &width, &height);
	data->img_player[1] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_semi_up.xpm", &width, &height);
	data->img_player[2] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_open_up.xpm", &width, &height);
}

void	animation_player_down(t_data *data)
{
	int	width;
	int	height;

	data->img_player[0] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_closed.xpm", &width, &height);
	data->img_player[1] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_semi_down.xpm", &width, &height);
	data->img_player[2] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_open_down.xpm", &width, &height);
}

void	animation_player_left(t_data *data)
{
	int	width;
	int	height;

	data->img_player[0] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_closed.xpm", &width, &height);
	data->img_player[1] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_semi_left.xpm", &width, &height);
	data->img_player[2] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_open_left.xpm", &width, &height);
}

void	animation_player_right(t_data *data)
{
	int	width;
	int	height;

	data->img_player[0] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_closed.xpm", &width, &height);
	data->img_player[1] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_semi_right.xpm", &width, &height);
	data->img_player[2] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_open_right.xpm", &width, &height);
}

void	animation_file(int keycode, t_data *data)
{
	free_previous_images(data);
	if (keycode == 119)
		animation_player_up(data);
	else if (keycode == 115)
		animation_player_down(data);
	else if (keycode == 97)
		animation_player_left(data);
	else if (keycode == 100)
		animation_player_right(data);
}
