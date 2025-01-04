/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:58:26 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/01/01 21:58:30 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "/home/mlabrirh/Downloads/minilibx-linux/mlx.h"

int close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	int i = 0;
	while (i < data->rows)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	exit(0);
	return (0);
}

int	loop(t_data *game)
{
	int	i;
	int	delay_us;

	i = 0;
	delay_us = 100000;
	while (i < game->rows * game->cols)
	{
		render_map(game);
		i++;
	}
	mlx_do_sync(game->mlx);
	usleep(delay_us);
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
    while ((line = get_next_line(fd)) != NULL)
    {
        if (data->cols == 0)
            data->cols = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n');
        update_map(data, line);
    }
    close(fd);
    return (data->rows > 0);
}

void	file_to_image(t_data data)
{
	int	width;
	int	height;
	data.mlx = mlx_init();
	if (!data.mlx)
		error_exit("Failed to initialize MLX");
	data.win = mlx_new_window(data.mlx, data.cols * 32, data.rows * 32, "Simple Map");
	if (!data.win)
		error_exit("Failed to create window");
//	initialize_player_position(&data);
	data.img_empty = mlx_xpm_file_to_image(data.mlx, "/home/mlabrirh/Downloads/Grass.xpm", &width, &height);
	data.img_wall = mlx_xpm_file_to_image(data.mlx, "/home/mlabrirh/Downloads/Window-2.xpm", &width, &height);
	data.img_collectible = mlx_xpm_file_to_image(data.mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_semi_right.xpm", &width, &height);		data.img_exit = mlx_xpm_file_to_image(data.mlx, "/home/mlabrirh/Desktop/sprites/Other/Portal/portal.xpm", &width, &height);
	data.img_player = mlx_xpm_file_to_image(data.mlx, "/home/mlabrirh/Desktop/sprites/Ghosts/B/ghost_down1.xpm", &width, &height);
	data.img_killer = mlx_xpm_file_to_image(data.mlx, "/home/mlabrirh/Desktop/sprites/Other/Pacdots/pacdot_powerup.xpm", &width, &height);
	if (!data.img_empty || !data.img_wall || !data.img_collectible || !data.img_exit || !data.img_player)
		error_exit("Failed to load images");	
	render_map(&data);
	mlx_key_hook(data.win, handle_keypress, &data);
	mlx_hook(data.win, 17, 0, (int (*)(void *))close_window, &data);
	mlx_loop(data.mlx);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("<map_file>\n");
		return (EXIT_FAILURE);
	}
	t_data data = {0};
	data.count_move = 0;
	if (!read_map(argv[1], &data))
		error_exit("Failed to read map");
	initialize_player_position(&data);
	if (!is_wall_consistent(data.map, data.rows, data.cols))
		exit(0);
	if (!compare_first_rows_with_other(data.map, data.rows, data.cols))
		exit(0);
	if (!is_path_to_exit(data, data.map))
		exit(0);
	if(!is_path_to_exit(data, data.map))
		exit(0);
	count_collect(&data);
	file_to_image(data);
	if (!validate_map(data.map, data.rows, data.cols))
		exit(0);
}
