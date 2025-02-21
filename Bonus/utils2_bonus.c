/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:29:49 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/27 16:29:54 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	validate_map(char *map[], int rows, int cols)
{
	int	counts[4];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	counts[3] = 0;
	count_elements(map, rows, cols, counts);
	return (validate_counts(counts));
}

void	free_previous_images(t_data *data)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (data->img_player[i])
		{
			mlx_destroy_image(data->mlx, data->img_player[i]);
			data->img_player[i] = NULL;
		}
		i++;
	}
}

int	animation_loop(t_data *data)
{
	static int	prev_frame;

	prev_frame = -1;
	data->frame_count++;
	if (data->frame_count >= 40000)
	{
		data->player_frame = (data->player_frame + 1) % 3;
		data->killer_frame = (data->killer_frame + 1) % 3;
		data->frame_count = 0;
		render_updated_tiles(data, &prev_frame);
	}
	return (0);
}

void	error_exit(const char *msg, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rows)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	perror(msg);
	exit(EXIT_SUCCESS);
}
