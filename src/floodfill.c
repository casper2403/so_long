/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstevens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:51:43 by cstevens          #+#    #+#             */
/*   Updated: 2025/02/19 10:51:51 by cstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**dup_map(char **map, int rows)
{
	int		i;
	char	**dup;

	dup = malloc(sizeof(char *) * (rows + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		dup[i] = ft_strdup(map[i]);
		if (!dup[i])
		{
			while (i-- > 0)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

static void	flood_fill(char **map, int x, int y, int rows, int cols)
{
	if (x < 0 || y < 0 || y >= rows || x >= cols)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == 'E')
	{
		map[y][x] = 'F';
		return ;
	}
	if (map[y][x] != '0' && map[y][x] != 'C' && map[y][x] != 'P')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, rows, cols);
	flood_fill(map, x - 1, y, rows, cols);
	flood_fill(map, x, y + 1, rows, cols);
	flood_fill(map, x, y - 1, rows, cols);
}

int	ft_floodfill(t_data *data)
{
	char	**dup;
	int		rows;
	int		cols;
	int		i;
	int		j;
	int		start_x;
	int		start_y;

	rows = data->grid_rows;
	cols = data->grid_cols;
	start_x = -1;
	start_y = -1;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (data->map[i][j] == 'P')
			{
				start_y = i;
				start_x = j;
				break ;
			}
			j++;
		}
		if (start_x != -1)
			break ;
		i++;
	}
	if (start_x == -1)
		return (0);
	dup = dup_map(data->map, rows);
	if (!dup)
		return (0);
	flood_fill(dup, start_x, start_y, rows, cols);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (dup[i][j] == 'C' || dup[i][j] == 'E')
			{
				while (i >= 0)
					free(dup[i--]);
				free(dup);
				write(1, "Error\nMap is not solveable", 26);
				return (0);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (dup[i])
		free(dup[i++]);
	free(dup);
	return (1);
}
