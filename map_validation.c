/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:56:39 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/01 21:56:44 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void count_collect(t_data *data)
{
	int i;
	int j;

	i = 0;
	data->collect = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			if (data->map[i][j] == 'C')
				data->collect++;
			j++;
		}
		i++;
	}
}

int compare_first_rows_with_other(char **map, int rows, int cols)
{
	int i;

	i = 0;
	while (i < rows)
	{
		if (ft_strlen(map[i]) != cols)
			return 1;
		i++;
	}
	return 0;
}

int is_wall_consistent(char **map, int rows, int cols)
{
	int i;
	int j;

	i = 0;
	while (i < cols)
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			return 0;
		i++;
	}
	j = 0;
	while (j < rows)
	{
		if (map[j][0] != '1' || map[j][cols - 1] != '1')
			return 0;
		j++;
	}
	return 1;
}

int validate_map(char *map[], int rows, int cols)
{
	int exit_count = 0;
	int collectible_count = 0;
	int player_count = 0;
	int killer = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j] == 'E')
				exit_count++;
			if (map[i][j] == 'C')
				collectible_count++;
			if (map[i][j] == 'P')
				player_count++;
			if (map[i][j] == 'T')
				killer++;
		}
	}

	if (exit_count != 1)
	{
		ft_putstr("Error: The map must contain exactly one exit.\n");
		return 0;
	}
	if (collectible_count < 1)
	{
		ft_putstr("Error: The map must contain at least one collectible.\n");
		return 0;
	}
	if (player_count != 1)
	{
		ft_putstr("Error: The map must contain exactly one player starting position.\n");
		return 0;
	}
	if (killer < 1)
	{
		ft_putstr("Error: The map must contain at least one killer.\n");
		return 0;
	}

	return 1;
}
