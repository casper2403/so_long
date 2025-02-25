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
		clean_resources(data);
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
	clean_resources(data);
	exit(0);
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

	ft_bzero(&data, sizeof(data));
	if (argc < 2)
	{
		ft_printf("Error\nusage: ./so_long <mapname>\n");
		exit(1);
	}
	if (read_map(argv[1], &data))
	{
		ft_printf("Error\nFile descriptor issue (probably)\n");
		clean_resources(&data);
		exit(1);
	}
	if (!ft_mapcheck(&data) || !ft_floodfill(&data)
		|| !init(&data) || !init_textures(&data) || create_grid(&data))
	{
		clean_resources(&data);
		exit(1);
	}
	mlx_hook(data.win, 2, 1L << 0, key_hook, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	clean_resources(&data);
	return (0);
}
