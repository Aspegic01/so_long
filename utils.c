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

void error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void ft_putstr(char *msg)
{
	write(1, msg, strlen(msg));
}

int validate_extension(const char *file, const char *ext)
{
	size_t len_file;
	size_t len_ext;

	len_file = strlen(file);
	len_ext = strlen(ext);
	if (len_file < len_ext)
		return (0);
	return (strncmp(file + len_file - len_ext, ext, len_ext) == 0);
}

void	file_to_image(t_data *data)
{
	int	i;

	data->img_empty = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Other/Walls/black.xpm", &data->width, &data->height);
	data->img_wall = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Other/Walls/wall.xpm", &data->width, &data->height);
	data->img_collectible = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Other/Pacdots/pacdot_powerup.xpm", &data->width, &data->height);		
	data->img_exit = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Other/Portal/portal.xpm", &data->width, &data->height);
	data->img_killer[0] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Ghosts/B/ghost_right1.xpm", &data->width, &data->height);
	data->img_killer[1] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Ghosts/B/ghost_down1.xpm", &data->width, &data->height);
	data->img_killer[2] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Ghosts/B/ghost_left2.xpm", &data->width, &data->height);
	data->img_player[0] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_closed.xpm", &data->width, &data->height);
	data->img_player[1] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_semi_left.xpm", &data->width, &data->height);
	data->img_player[2] = mlx_xpm_file_to_image(data->mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_open_left.xpm", &data->width, &data->height);
	
	i = 0;
	while (i < 3)
	{
		if (!data->img_player[i] && !data->img_killer[i])
			error_exit("Failed to load animation frames");
		i++;
	}
	data->player_frame = 0;
	data->killer_frame = 0;
	data->frame_count = 0;
	if (!data->img_empty || !data->img_wall || !data->img_collectible || !data->img_exit ||
	!data->img_player[i] || !data->img_killer[i])
		error_exit("Failed to load images");	
}

void initialize_player_position(t_data *data)
{
	int y = 0;
	while (y < data->rows)
	{
		int x = 0;
		while (x < data->cols)
		{
			if (data->map[y][x] == 'P')
			{
				data->player_x = x;
				data->player_y = y;
				return;
			}
			x++;
		}
		y++;
	}
}
