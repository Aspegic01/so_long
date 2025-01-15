/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:58:26 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/15 20:07:41 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "so_long.h"
#include "/home/mlabrirh/Downloads/minilibx-linux/mlx.h"
#include <unistd.h>

int	close_window(t_data *data)
{
	int	i;

	mlx_destroy_window(data->mlx, data->win);
	i = 0;
	while (i < data->rows)
	{
		free(data->map[i]);
		i++;
	}
	exit(0);
	return (0);
}

void	update_map(t_data *data, char *line)
{
	char	**new_map;
	size_t	i;

	new_map = malloc(sizeof(char *) * (data->rows + 1));
	if (!new_map)
		error_exit("Memory allocation failed");
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
		error_exit("Invalid file extension. Only '.ber' files are allowed.");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Error opening map file");
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
	data.mlx = mlx_init();
	if (!data.mlx)
		error_exit("Failed to initialize MLX");
	data.win = mlx_new_window(data.mlx,
			data.cols * 32, data.rows * 32, "Simple Map");
	if (!data.win)
		error_exit("Failed to create window");
	file_to_image(&data);
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
			error_exit("Failed to read map");
		initialize_player_position(&data);
		if (!is_wall_consistent(data.map, data.rows, data.cols))
			exit(0);
		if (!compare_first_rows_with_other(data.map, data.rows, data.cols))
			exit(0);
		if (!validate_map(data.map, data.rows, data.cols))
			exit(0);
		if (!is_path_to_exit(data, data.map))
			exit(0);
		if (!is_path_to_collect(data, data.map))
			exit(0);
		count_collect(&data);
		mlx_function(data);
		if (!validate_map(data.map, data.rows, data.cols))
			exit(0);
	}
	ft_putstr("map.ber\n");
	exit(0);
}
