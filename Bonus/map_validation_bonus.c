/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:57:43 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/27 20:57:44 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include <stddef.h>

void	count_collect(t_data *data)
{
	int	i;
	int	j;

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

int	compare_first_rows_with_other(char **map, size_t rows, size_t cols)
{
	size_t	i;

	i = -1;
	while (i < rows)
	{
		if (ft_strlen(map[i]) != cols)
			return (0);
	}
	return (1);
}

int	is_wall_consistent(char **map, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < cols)
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			return (0);
		i++;
	}
	j = 1;
	while (j < rows)
	{
		if (map[j][0] != '1' || map[j][cols - 1] != '1')
			return (0);
		j++;
	}
	return (1);
}

void	count_elements(char *map[], int rows, int cols, int *counts)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map[i][j] == 'E')
				counts[0]++;
			if (map[i][j] == 'C')
				counts[1]++;
			if (map[i][j] == 'P')
				counts[2]++;
			if (map[i][j] == 'T')
				counts[3]++;
			j++;
		}
		i++;
	}
}

int	validate_counts(int *counts)
{
	if (counts[0] != 1)
	{
		ft_putstr("The map must contain exactly one exit.\n");
		return (0);
	}
	if (counts[1] < 1)
	{
		ft_putstr("Error: The map must contain at least one collectible.\n");
		return (0);
	}
	if (counts[2] != 1)
	{
		ft_putstr("Error: The map must contain exactly one player.\n");
		return (0);
	}
	if (counts[3] < 1)
	{
		ft_putstr("Error: The map must contain at least one killer.\n");
		return (0);
	}
	return (1);
}
