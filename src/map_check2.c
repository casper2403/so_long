/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstevens <cstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:56:17 by cstevens          #+#    #+#             */
/*   Updated: 2025/02/25 21:56:19 by cstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_rectangle(t_data *data)
{
	int	row;
	int	len;

	if (!data->map || !data->map[0])
		return (0);
	len = ft_strlen(data->map[0]);
	row = 1;
	while (data->map[row])
	{
		if ((int)ft_strlen(data->map[row]) != len)
		{
			ft_printf("Error\nMap is not rectangular\n");
			return (0);
		}
		row++;
	}
	data->grid_cols = len;
	return (1);
}

int	check_closed(t_data *data)
{
	int	row;
	int	col;
	int	len;
	int	total_rows;

	if (!data->map || !data->map[0])
		return (0);
	len = ft_strlen(data->map[0]);
	total_rows = 0;
	while (data->map[total_rows])
		total_rows++;
	row = 0;
	while (row < total_rows)
	{
		col = 0;
		while (col < len)
		{
			if ((row == 0 || row == total_rows - 1 || col == 0
					|| col == len - 1) && data->map[row][col] != '1')
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}
