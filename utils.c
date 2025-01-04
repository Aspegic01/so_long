/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:56:03 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/01 21:56:24 by mlabrirh         ###   ########.fr       */
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
	error_exit("Player position not found in map");
}
