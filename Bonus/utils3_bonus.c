/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:30:23 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/27 16:30:25 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_putstr(char *msg)
{
	write(1, msg, ft_strlen(msg));
}

void	render_updated_tiles(t_data *data, int *prev_frame)
{
	int	x;
	int	y;

	if (data->player_frame != *prev_frame || data->killer_frame != *prev_frame)
	{
		y = 0;
		while (y < data->rows)
		{
			x = 0;
			while (x < data->cols)
			{
				if (data->map[y][x] == 'P' || data->map[y][x] == 'T')
					render_tile(data, x, y);
				x++;
			}
			y++;
		}
		*prev_frame = data->player_frame;
	}
}

void	file_holder(t_data *data)
{
	data->digit[0] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Fonts/0.xpm", &data->width, &data->height);
	data->digit[1] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Fonts/1.xpm", &data->width, &data->height);
	data->digit[2] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Fonts/2.xpm", &data->width, &data->height);
	data->digit[3] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Fonts/3.xpm", &data->width, &data->height);
	data->digit[4] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Fonts/4.xpm", &data->width, &data->height);
	data->digit[5] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Fonts/5.xpm", &data->width, &data->height);
	data->digit[6] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Fonts/6.xpm", &data->width, &data->height);
	data->digit[7] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Fonts/7.xpm", &data->width, &data->height);
	data->digit[8] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Fonts/8.xpm", &data->width, &data->height);
	data->digit[9] = mlx_xpm_file_to_image(data->mlx, \
	"./sprites/Other/Fonts/9.xpm", &data->width, &data->height);
}

void	render_digit(t_data *data, int x, int y)
{
	int		digit;
	int		i;
	char	*buffer;

	i = 0;
	buffer = ft_itoa(data->count_move);
	if (!buffer)
		error_exit("Memory allocation failed", data);
	while (buffer[i])
	{
		digit = buffer[i] - '0';
		mlx_put_image_to_window(data->mlx, data->win, \
		data->digit[digit], x + (i * 32), y);
		i++;
	}
	free(buffer);
}

int	map_va(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->rows)
	{
		x = 0;
		while (x < data->cols)
		{
			if (data->map[y][x] != 'P' && data->map[y][x] != 'C'\
				&&data->map[y][x] != '1' && data->map[y][x] != '0'\
				&& data->map[y][x] != 'E' && data->map[y][x] != 'T')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
