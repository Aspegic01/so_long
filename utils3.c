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
