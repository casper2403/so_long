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

int	init(t_data *data, int cols, int rows)
{
	int	img_width;
	int	img_height;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->grid_cols = cols;
	data->grid_rows = rows;
	data->win_width = cols * TILE_SIZE;
	data->win_height = rows * TILE_SIZE;
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, "Tile Grid");
	if (!data->win)
		return (0);
	data->tile_img = mlx_xpm_file_to_image(data->mlx,
			"assets/sprites/cave water stalagmite.xpm",
			&img_width, &img_height);
	if (!data->tile_img || img_width != TILE_SIZE || img_height != TILE_SIZE)
		return (0);
	return (1);
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
		{
			mlx_put_image_to_window(
				data->mlx, data->win, data->tile_img,
				x * TILE_SIZE,
				y * TILE_SIZE);
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init(&data, 20, 15))
		exit(1);
	create_grid(&data);
	mlx_loop(data.mlx);
	return (0);
}
