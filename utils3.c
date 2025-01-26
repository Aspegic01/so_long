/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:27:51 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/21 17:53:22 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		*prev_frame = data->killer_frame;
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

void	put_digit(t_data *data, int digit, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->win, data->digit[digit], x, y);
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
		put_digit(data, digit, x + (i * 32), y);
		i++;
	}
	free(buffer);
}
