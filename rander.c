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
#include "mlx.h"
#include <string.h>

void put_image(t_data *data, char tile, int x, int y)
{
	void	*img;
	char	*count;
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
		img = data->img_player[data->player_frame];
	else if (tile == 'T')
		img = data->img_killer[data->killer_frame];

	if (img)
	{
		count = ft_itoa(data->count_move);
		mlx_put_image_to_window(data->mlx, data->win, img, x * 32, y * 32);
		mlx_string_put(data->mlx, data->win, 20, 20, 0xFFFFFF, "MOVE :");
		mlx_string_put(data->mlx, data->win, 70, 20, 0xFFFFFF,count);
	}
}
void render_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->rows)
	{
		x = 0;
		while (x < data->cols)
		{
			put_image(data, data->map[y][x], x, y);
			x++;
		}
		y++;
	}
}
