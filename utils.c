/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:56:03 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/15 19:47:32 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <string.h>
#include "so_long.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	validate_extension(const char *file, const char *ext)
{
	size_t	len_file;
	size_t	len_ext;

	len_file = ft_strlen(file);
	len_ext = ft_strlen(ext);
	if (len_file < len_ext)
		return (0);
	return (ft_strncmp(file + len_file - len_ext, ext, len_ext) == 0);
}

void	free_file_to_image(t_data *data)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (data->img_killer[i] && data->img_player[i])
		{
			mlx_destroy_image(data->mlx, data->img_killer[i]);
			mlx_destroy_image(data->mlx, data->img_player[i]);
		}
		i++;
	}
	free_digit_image(data);
	if (data->img_empty)
		mlx_destroy_image(data->mlx, data->img_empty);
	if (data->img_wall)
		mlx_destroy_image(data->mlx, data->img_wall);
	if (data->img_collectible)
		mlx_destroy_image(data->mlx, data->img_collectible);
	if (data->img_exit)
		mlx_destroy_image(data->mlx, data->img_exit);
}

void	file_player_and_killer(t_data *data)
{
	data->img_killer[0] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Ghosts/B/ghost_right1.xpm", &data->width, &data->height);
	data->img_killer[1] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Ghosts/B/ghost_down1.xpm", &data->width, &data->height);
	data->img_killer[2] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Ghosts/B/ghost_left2.xpm", &data->width, &data->height);
	data->img_player[0] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_closed.xpm", &data->width, &data->height);
	data->img_player[1] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_semi_left.xpm", &data->width, &data->height);
	data->img_player[2] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Pac-Man/pac_open_left.xpm", &data->width, &data->height);
	if (!data->img_player[0] || !data->img_player[1] || !data->img_player[2] || \
		!data->img_killer[0] || !data->img_killer[1] || !data->img_killer[2])
	{
		close_window(data);
		error_exit("Failed to load images", data);
	}
	data->player_frame = 0;
	data->killer_frame = 0;
	data->frame_count = 0;
}

void	file_to_image(t_data *data)
{
	data->img_empty = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Walls/black.xpm", &data->width, &data->height);
	data->img_wall = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Walls/wall.xpm", &data->width, &data->height);
	data->img_collectible = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Pacdots/pacdot_powerup.xpm", &data->width, &data->height);
	data->img_exit = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Portal/portal.xpm", &data->width, &data->height);
	file_player_and_killer(data);
	if (!data->img_empty || !data->img_wall || \
		!data->img_collectible || !data->img_exit)
	{
		close_window(data);
		error_exit("Failed to load images", data);
	}
}

void	initialize_player_position(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->rows)
	{
		x = 0;
		while (x < data->cols)
		{
			if (data->map[y][x] == 'P')
			{
				data->player_x = x;
				data->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
