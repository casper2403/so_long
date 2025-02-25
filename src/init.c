/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstevens <cstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:00:02 by cstevens          #+#    #+#             */
/*   Updated: 2025/02/25 22:00:24 by cstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (!data->wall_img || !data->player_img || !data->tile_img
		|| !data->collectible_img || !data->exit_img)
	{
		clean_resources(data);
		return (0);
	}
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
		return (ft_printf("Error\nInvalid map\n"));
	mlx_put_image_to_window(data->mlx, data->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
	return (0);
}

static int	add_line(t_data *data, char *line, int count)
{
	char	**tmp;

	tmp = ft_realloc(data->map, sizeof(char *) * (count + 1),
			sizeof(char *) * (count + 2));
	if (!tmp)
	{
		free(line);
		free_map(data->map);
		return (-1);
	}
	data->map = tmp;
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	data->map[count] = line;
	return (count + 1);
}

int	read_map(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	data->map = NULL;
	line = get_next_line(fd);
	while (line)
	{
		count = add_line(data, line, count);
		if (count == -1)
			return (1);
		line = get_next_line(fd);
	}
	if (data->map)
		data->map[count] = NULL;
	data->grid_rows = count;
	close(fd);
	return (0);
}
