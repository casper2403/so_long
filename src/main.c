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
#include "../lib/mlx_linux/mlx.h"
#include "../lib/libft/libft.h"
#include "so_long.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <X11/keysym.h>

int	key_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
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

void	put_tile(int x, int y, t_data *data)
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
		img = data->tile_img;
	mlx_put_image_to_window(data->mlx, data->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

int	read_map(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		count;
	char	**tmp;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	data->map = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = realloc(data->map, sizeof(char *) * (count + 2));
		if (!tmp)
		{
			free(line);
			return (1);
		}
		data->map = tmp;
		data->map[count] = line;
		count++;
		data->grid_cols = ft_strlen(line);
		line = get_next_line(fd);
	}
	data->grid_rows = count;
	if (data->map)
		data->map[count] = NULL;
	close(fd);
	return (0);
}

void	create_grid(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->grid_rows)
	{
		x = -1;
		while (++x < data->grid_cols)
			put_tile(x, y, data);
	}
}

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map && data->map[i])
	{
		ft_printf("%s", data->map[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		exit(1);
	if (read_map(argv[1], &data))
		exit(1);
	print_map(&data);
	if (!init(&data))
		exit(1);
	if (!init_textures(&data))
		exit(1);
	create_grid(&data);
	mlx_hook(data.win, 2, 1L << 0, key_hook, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
