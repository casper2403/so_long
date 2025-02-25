/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstevens <cstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:51:59 by cstevens          #+#    #+#             */
/*   Updated: 2025/02/25 21:52:01 by cstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_exit(t_data *data)
{
	int	row;
	int	col;
	int	exit_count;

	exit_count = 0;
	row = 0;
	while (data->map && data->map[row])
	{
		col = 0;
		while (data->map[row][col])
		{
			if (data->map[row][col] == 'E')
				exit_count++;
			col++;
		}
		row++;
	}
	if (exit_count != 1)
		ft_printf("Error\nInvalid amount of exits\n");
	return (exit_count == 1);
}

int	check_player(t_data *data)
{
	int	row;
	int	col;
	int	player_count;

	player_count = 0;
	row = -1;
	while (data->map && data->map[++row])
	{
		col = -1;
		while (data->map[row][++col])
		{
			if (data->map[row][col] == 'P')
			{
				data->player_x = col;
				data->player_y = row;
				player_count++;
			}
		}
	}
	if (player_count != 1)
		ft_printf("Error\nInvalid amount of players\n");
	return (player_count == 1);
}

int	check_collectible(t_data *data)
{
	int	row;
	int	col;
	int	collectible_count;

	collectible_count = 0;
	row = 0;
	while (data->map && data->map[row])
	{
		col = 0;
		while (data->map[row][col])
		{
			if (data->map[row][col] == 'C')
				collectible_count++;
			col++;
		}
		row++;
	}
	if (collectible_count < 1)
		ft_printf("Error\nInvalid amount of collectibles\n");
	return (collectible_count >= 1);
}

int	ft_mapcheck(t_data *data)
{
	if (!check_exit(data))
		return (0);
	else if (!check_player(data))
		return (0);
	else if (!check_collectible(data))
		return (0);
	else if (!check_rectangle(data))
		return (0);
	else if (!check_closed(data))
	{
		ft_printf("Error\nMap not closed off\n");
		return (0);
	}
	return (1);
}
