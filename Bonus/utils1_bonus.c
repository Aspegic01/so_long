/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:29:26 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/27 16:29:28 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	flood_fill(t_data *data, char **map_copy, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->rows || y >= data->cols)
		return ;
	if (map_copy[x][y] == '1' || map_copy[x][y] == '.' || map_copy[x][y] == 'T')
		return ;
	if (data->ignore_exit == 1 && map_copy[x][y] == 'E')
		return ;
	map_copy[x][y] = '.';
	flood_fill(data, map_copy, x + 1, y);
	flood_fill(data, map_copy, x - 1, y);
	flood_fill(data, map_copy, x, y + 1);
	flood_fill(data, map_copy, x, y - 1);
}

void	free_map_copy(char **map_copy, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

char	**copy_map(t_data data, char **map)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(data.rows * sizeof(char *));
	if (!map_copy)
		error_exit("Memory allocation failed", &data);
	i = 0;
	while (i < data.rows)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			free_map_copy(map_copy, i);
			error_exit("Memory allocation failed", &data);
		}
		i++;
	}
	return (map_copy);
}

int	is_path_to_collect(t_data data, char **map)
{
	char	**map_copy;
	int		x;
	int		y;

	data.ignore_exit = 1;
	map_copy = copy_map(data, map);
	flood_fill(&data, map_copy, data.player_y, data.player_x);
	y = 0;
	while (y < data.rows)
	{
		x = 0;
		while (x < data.cols)
		{
			if (map[y][x] == 'C' && map_copy[y][x] != '.')
			{
				free_map_copy(map_copy, data.rows);
				return (0);
			}
			x++;
		}
		y++;
	}
	free_map_copy(map_copy, data.rows);
	return (1);
}

int	is_path_to_exit(t_data data, char **map)
{
	char	**map_copy;
	int		x;
	int		y;

	data.ignore_exit = 0;
	map_copy = copy_map(data, map);
	flood_fill(&data, map_copy, data.player_y, data.player_x);
	y = 0;
	while (y < data.rows)
	{
		x = 0;
		while (x < data.cols)
		{
			if (map[y][x] == 'E' && map_copy[y][x] != '.')
			{
				free_map_copy(map_copy, data.rows);
				return (0);
			}
			x++;
		}
		y++;
	}
	free_map_copy(map_copy, data.rows);
	return (1);
}
