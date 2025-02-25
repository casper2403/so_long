/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstevens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:55:51 by cstevens          #+#    #+#             */
/*   Updated: 2025/02/25 12:55:58 by cstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_collectibles(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->grid_rows)
	{
		x = -1;
		while (++x < data->grid_cols)
			if (data->map[y][x] == 'C')
				return (0);
	}
	return (1);
}

void	replace_tile(t_data *data, int new_x, int new_y, int *moves)
{
	data->map[data->player_y][data->player_x] = '0';
	data->map[new_y][new_x] = 'P';
	data->player_x = new_x;
	data->player_y = new_y;
	mlx_clear_window(data->mlx, data->win);
	create_grid(data);
	ft_printf("Amount of moves: %d\n", (*moves)++);
}

void	move_player(t_data *data, int dx, int dy)
{
	int			new_x;
	int			new_y;
	char		tile;
	static int	moves = 1;

	new_x = data->player_x + dx;
	new_y = data->player_y + dy;
	if (new_x < 0 || new_x >= data->grid_cols
		|| new_y < 0 || new_y >= data->grid_rows)
		return ;
	tile = data->map[new_y][new_x];
	if (tile == '0' || tile == 'C')
		replace_tile(data, new_x, new_y, &moves);
	else if (tile == 'E')
	{
		if (check_collectibles(data))
		{
			replace_tile(data, new_x, new_y, &moves);
			ft_printf("You've won!!!\n");
			mlx_destroy_window(data->mlx, data->win);
			clean_resources(data);
			exit(0);
		}
	}
}
