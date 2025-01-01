
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img_empty;
    void    *img_wall;
    void    *img_collectible;
    void    *img_exit;
    void    *img_player;
	void	*img_killer;
    int     player_x;
    int     player_y;
    char    **map;
    int     rows;
    int     cols;
	int		collect;
}   t_data;

void    error_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void	ft_putstr(char *msg)
{
	write(1, msg, ft_strlen(msg));
}

void	count_collect(t_data *data)
{
	int i = 0;
	data->collect = 0;
	while(i < data->rows)
	{
		int j = 0;
		while(j < data->cols)
		{
			if (data->map[i][j] == 'C')
			{
				data->collect++;
			}
			j++;
		}
		i++;
	}
}

int	compare_firt_rows_with_other(char **map, int rows, int cols)
{
	int	i = 0;

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
	int	i = 0;
	int	j = 0;

    while (i < cols)
	{
        if (map[0][i] != '1' || map[rows - 1][i] != '1')
			return 0;
		i++;
    }
    while (j < rows)
	{
        if (map[j][0] != '1' || map[j][cols - 1] != '1')
            return 0;
		j++;
    }
    return 1; 
}


int	validate_extension(const char *file, const char *ext)
{
	size_t	len_file;
	size_t	len_ext;

	len_file = ft_strlen(file);
	len_ext = ft_strlen(ext);
	if (len_file < len_ext)
		return (0);
	return (ft_strncmp(file + len_file - len_ext, ext, len_ext) == 0);
}

int validate_map(char *map[], int rows, int cols)
{
    int exit_count = 0;
    int collectible_count = 0;
    int player_count = 0;
	int	killer = 0;
	int	i = 0;
	int	j;

    while (i < rows)
    {
		j = 0;
        while (j < cols)
        {
            if (map[i][j] == 'E')
                exit_count++;
			if (map[i][j] == 'C')
                collectible_count++;
			if (map[i][j] == 'P')
                player_count++;
			if (map[i][j] == 'T')
				killer++;

			j++;
        }
		i++;
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

int	read_map(const char *file, t_data *data)
{
	int		fd;
	char	*line;
	char	**new_map;
	size_t	i;
	
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
	close(fd);
	return (data->rows > 0);
}

void put_image(t_data *data, char tile, int x, int y)
{
    void *img = NULL;
	int i = data->player_x + data->player_y;

    if (tile == '0')
        img = data->img_empty;
    else if (tile == '1')
        img = data->img_wall;
    else if (tile == 'C')
        img = data->img_collectible;
    else if (tile == 'E')
        img = data->img_exit;
    else if (tile == 'P')
        img = data->img_player;
    else if (tile == 'T')
		img = data->img_killer;

    if (img)
        mlx_put_image_to_window(data->mlx, data->win, img, x * 32, y * 32);
		mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, "MOVE : %d");

}

void render_map(t_data *data)
{
    int y = 0;
    while (y < data->rows)
    {
        int x = 0;
        while (x < data->cols)
        {
            put_image(data, data->map[y][x], x, y);
            x++;
        }
        y++;
    }
}

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

void	move_player(t_data *data, int new_x, int new_y)
{
	data->map[data->player_y][data->player_x] = '0';
	data->player_x = new_x;
	data->player_y = new_y;
	data->map[data->player_y][data->player_x] = 'P';
}

int is_valid_move(t_data *data, int x, int y)
{
    if (x < 0 || y < 0 || x >= data->cols || y >= data->rows)
        return (0);
    char tile = data->map[y][x];
    return (tile == '0' || tile == 'C' || tile == 'E' || tile == 'T');
}

void process_interaction(t_data *data, int x, int y)
{
    char tile = data->map[y][x];
	int	i = 0;
    if (tile == 'C')
    {
        data->collect--;
        data->map[y][x] = '0';  
    }
    else if (tile == 'E')
    {
        if (data->collect == 0)
        {
            move_player(data, x, y);
            close_window(data); 
        }
        return;
    }
    else if (tile == 'T')
    {
        move_player(data, x, y);
        close_window(data);
    }

    move_player(data, x, y);
}


int handle_keypress(int keycode, t_data *data)
{
    int new_x = data->player_x;
    int new_y = data->player_y;

    if (keycode == 65307)
        close_window(data);
    else if (keycode == 119)
        new_y--;
    else if (keycode == 115)
        new_y++;
    else if (keycode == 97)
        new_x--;
    else if (keycode == 100)
        new_x++;

    if (is_valid_move(data, new_x, new_y))
    {
        process_interaction(data, new_x, new_y);
        mlx_clear_window(data->mlx, data->win);
        render_map(data);
    }
    return (0);
}

void flood_fill(t_data *data, char **map_copy, int x, int y)
{
    if (x < 0 || y < 0 || x >= data->rows || y >= data->cols)
        return;
    if (map_copy[x][y] == '1' || map_copy[x][y] == '.')
        return;
    map_copy[x][y] = '.';
    flood_fill(data, map_copy, x + 1, y);
    flood_fill(data, map_copy, x - 1, y);
    flood_fill(data, map_copy, x, y + 1);
    flood_fill(data, map_copy, x, y - 1);
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


int is_path_to_exit(t_data data, char **map)
{
    char **map_copy = malloc(data.rows * sizeof(char *));
    if (!map_copy)
        error_exit("Memory allocation failed");
	int i = 0; 
	while (i < data.rows)
	{
        map_copy[i] = ft_strdup(map[i]);
		i++;
	}
    flood_fill(&data, map_copy, data.player_y, data.player_x);
	int	y = 0;
    while (y < data.rows)
	{
		int	x = 0;
        while (x < data.cols)
		{
            if (map[y][x] == 'E' && map_copy[y][x] != '.')
            {
				int	j = 0;
                while (j < data.rows)
				{
                    free(map_copy[i]);
					j++;
				}
                free(map_copy);
                return 0;
            }
			x++;
        }
		y++;
    }
	int e = 0;
    while (e < data.rows)
	{
		free(map_copy[e]);
		e++;
	}
    free(map_copy);
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
		ft_putstr("<map_file>\n");
        return (EXIT_FAILURE);
    }
    t_data data = {0};

    if (!read_map(argv[1], &data))
        error_exit("Failed to read map");
    initialize_player_position(&data);
	if (!is_wall_consistent(data.map, data.rows, data.cols))
		exit(0);
	if (!compare_firt_rows_with_other(data.map, data.rows, data.cols))
		exit(0);
	if (!is_path_to_exit(data, data.map))
		exit(0);
    data.mlx = mlx_init();
    if (!data.mlx)
        error_exit("Failed to initialize MLX");
    data.win = mlx_new_window(data.mlx, data.cols * 32, data.rows * 32, "Simple Map");
    if (!data.win)
        error_exit("Failed to create window");
	count_collect(&data);
    int width, height;
    data.img_empty = mlx_xpm_file_to_image(data.mlx, "/home/mlabrirh/Downloads/Grass.xpm", &width, &height);
    data.img_wall = mlx_xpm_file_to_image(data.mlx, "/home/mlabrirh/Downloads/Window-2.xpm", &width, &height);
    data.img_collectible = mlx_xpm_file_to_image(data.mlx, "/home/mlabrirh/Desktop/sprites/Pac-Man/pac_semi_right.xpm", &width, &height);
    data.img_exit = mlx_xpm_file_to_image(data.mlx, "/home/mlabrirh/Desktop/sprites/Other/Portal/portal.xpm", &width, &height);
    data.img_player = mlx_xpm_file_to_image(data.mlx, "/home/mlabrirh/Desktop/sprites/Ghosts/B/ghost_down1.xpm", &width, &height);
	data.img_killer = mlx_xpm_file_to_image(data.mlx, "/home/mlabrirh/Desktop/sprites/Other/Pacdots/pacdot_powerup.xpm", &width, &height);
    if (!data.img_empty || !data.img_wall || !data.img_collectible || !data.img_exit || !data.img_player)
        error_exit("Failed to load images");
	if (!validate_map(data.map, data.rows, data.cols))
		exit(0);
    render_map(&data);
    mlx_key_hook(data.win, handle_keypress, &data);
    mlx_hook(data.win, 17, 0, (int (*)(void *))close_window, &data);
    mlx_loop(data.mlx);
}
