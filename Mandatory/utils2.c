/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:00:59 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/21 18:19:57 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	exit(EXIT_FAILURE);
}
