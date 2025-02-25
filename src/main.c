/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstevens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:27:51 by cstevens          #+#    #+#             */
/*   Updated: 2025/02/17 15:27:53 by cstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	key_hook(int keycode, t_data *data)
{
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (keycode == XK_w || keycode == XK_Up)
		dy = -1;
	else if (keycode == XK_s || keycode == XK_Down)
		dy = 1;
	else if (keycode == XK_a || keycode == XK_Left)
		dx = -1;
	else if (keycode == XK_d || keycode == XK_Right)
		dx = 1;
	if (dx || dy)
		move_player(data, dx, dy);
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int	init_textures(t_data *data)
{
	int	img_width;
	int	img_height;

	data->wall_img = mlx_xpm_file_to_image(data->mlx,
			"assets/sprites/cavewater.xpm",
			&img_width, &img_height);
	data->player_img = mlx_xpm_file_to_image(data->mlx,
			"assets/sprites/landcoralblack.xpm",
			&img_width, &img_height);
	data->tile_img = mlx_xpm_file_to_image(data->mlx,
			"assets/sprites/path.xpm",
			&img_width, &img_height);
	data->collectible_img = mlx_xpm_file_to_image(data->mlx,
			"assets/sprites/coral blue.xpm",
			&img_width, &img_height);
	data->exit_img = mlx_xpm_file_to_image(data->mlx,
			"assets/sprites/coralyellow.xpm",
			&img_width, &img_height);
	if (!data->wall_img || !data->player_img || !data->tile_img ||
		!data->collectible_img || !data->exit_img)
		return (0);
	return (1);
}

int	init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->win_width = data->grid_cols * TILE_SIZE;
	data->win_height = data->grid_rows * TILE_SIZE;
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, "Tile Grid");
	if (!data->win)
		return (0);
	return (1);
}

int	put_tile(int x, int y, t_data *data)
{
	char	tile;
	void	*img;

	tile = data->map[y][x];
	if (tile == '1')
		img = data->wall_img;
	else if (tile == '0')
		img = data->tile_img;
	else if (tile == 'C')
		img = data->collectible_img;
	else if (tile == 'P')
		img = data->player_img;
	else if (tile == 'E')
		img = data->exit_img;
	else
		return (write(1, "Error\nMap contains invalid character", 36));
	mlx_put_image_to_window(data->mlx, data->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
	return (0);
}

int	read_map(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		count;
	char	**tmp;
	int		i;
	int		found;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	data->map = NULL;
	found = 0;
	line = get_next_line(fd);
	while (line)
	{
		tmp = realloc(data->map, sizeof(char *) * (count + 2));
		if (!tmp)
		{
			free(line);
			return (1);
		}
		data->map = tmp;
		if (ft_strlen(line) && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		data->map[count] = line;
		i = 0;
		while (line[i])
		{
			if (line[i] == 'P' && !found)
			{
				data->player_x = i;
				data->player_y = count;
				found = 1;
			}
			i++;
		}
		count++;
		line = get_next_line(fd);
	}
	if (data->map)
		data->map[count] = NULL;
	data->grid_rows = count;
	if (data->grid_rows > 0)
		data->grid_cols = ft_strlen(data->map[0]);
	else
		data->grid_cols = 0;
	close(fd);
	if (!found)
		return (1);
	return (0);
}

int	create_grid(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->grid_rows)
	{
		x = -1;
		while (++x < data->grid_cols)
			if (put_tile(x, y, data))
				return (1);
	}
	return (0);
}

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map && data->map[i])
	{
		ft_printf("%s\n", data->map[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
	{
		ft_printf("Error\nusage: ./so_long <mapname>\n");
		exit(1);
	}
	if (read_map(argv[1], &data))
		exit(1);
	print_map(&data);
	if (!ft_floodfill(&data))
		exit(1);
	if (!init(&data))
		exit(1);
	if (!init_textures(&data))
		exit(1);
	if (create_grid(&data))
		exit(1);
	mlx_hook(data.win, 2, 1L << 0, key_hook, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
