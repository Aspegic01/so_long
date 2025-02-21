/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:57:14 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/01 21:57:24 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_data *data, char tile, int x, int y)
{
	void	*img;

	img = NULL;
	if (tile == '0')
		img = data->img_empty;
	else if (tile == '1')
		img = data->img_wall;
	else if (tile == 'C')
		img = data->img_collectible;
	else if (tile == 'E')
		img = data->img_exit;
	else if (tile == 'P')
		img = data->img_player;
	if (img)
		mlx_put_image_to_window(data->mlx, data->win, img, x * 32, y * 32);
}

void	render_tile(t_data *data, int x, int y)
{
	put_image(data, data->map[y][x], x, y);
}

void	render_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->rows)
	{
		x = 0;
		while (x < data->cols)
		{
			render_tile(data, x, y);
			x++;
		}
		y++;
	}
}
