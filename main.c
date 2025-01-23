/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:58:26 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/21 18:42:59 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "so_long.h"
#include <mlx.h>
#include <unistd.h>

int	close_window(t_data *data)
{
	int	i;

	free_file_to_image(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->map)
	{
		i = 0;
		while (i < data->rows)
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
	return (0);
}

void	update_map(t_data *data, char *line)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (data->rows + 1));
	if (!new_map)
		error_exit("Memory allocation failed", data);
	i = 0;
	while (i < data->rows)
	{
		new_map[i] = data->map[i];
		i++;
	}
	new_map[data->rows] = line;
	free(data->map);
	data->map = new_map;
	data->rows++;
}

int	read_map(const char *file, t_data *data)
{
	int		fd;
	char	*line;

	if (!validate_extension(file, ".ber"))
		error_exit("Only '.ber' files are allowed.", data);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Error opening map file", data);
	data->rows = 0;
	data->cols = 0;
	data->map = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (data->cols == 0)
			data->cols = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n');
		update_map(data, line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (data->rows);
}

void	mlx_function(t_data data)
{
	data.frame_count = 0;
	data.mlx = mlx_init();
	if (!data.mlx)
		error_exit("Failed to initialize MLX", &data);
	data.win = mlx_new_window(data.mlx,
			data.cols * 32, data.rows * 36, "Simple Map");
	if (!data.win)
		error_exit("Failed to create window", &data);
	file_to_image(&data);
	file_holder(&data);
	render_map(&data);
	mlx_key_hook(data.win, handle_keypress, &data);
	mlx_hook(data.win, 2, 1L << 0, keypress_handler, &data);
	mlx_hook(data.win, 17, 0, (int (*)(void *))close_window, &data);
	mlx_loop_hook(data.mlx, animation_loop, &data);
	mlx_loop(data.mlx);
	close_window(&data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		data.count_move = 0;
		if (!read_map(argv[1], &data))
			error_exit("Failed to read map", &data);
		initialize_player_position(&data);
		if (!is_wall_consistent(data.map, data.rows, data.cols))
			error_exit("is wall not consistent", &data);
		if (!compare_first_rows_with_other(data.map, data.rows, data.cols))
			error_exit("The map is not valid", &data);
		if (!validate_map(data.map, data.rows, data.cols))
			error_exit("The map is not valid", &data);
		if (!is_path_to_exit(data, data.map))
			error_exit("That is no path to exit", &data);
		if (!is_path_to_collect(data, data.map))
			error_exit("That is no path to collect", &data);
		count_collect(&data);
		mlx_function(data);
		if (!validate_map(data.map, data.rows, data.cols))
			error_exit("The map is not valid", &data);
	}
	ft_putstr("map.ber\n");
	exit(0);
}
