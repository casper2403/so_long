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

static void	flood_fill(t_flood_fill *f, int x, int y)
{
	if (x < 0 || y < 0 || y >= f->rows || x >= f->cols)
		return ;
	if (f->map[y][x] == '1' || f->map[y][x] == 'F')
		return ;
	if (f->map[y][x] == 'E')
	{
		f->map[y][x] = 'F';
		return ;
	}
	if (f->map[y][x] != '0' && f->map[y][x] != 'C' && f->map[y][x] != 'P')
		return ;
	f->map[y][x] = 'F';
	flood_fill(f, x + 1, y);
	flood_fill(f, x - 1, y);
	flood_fill(f, x, y + 1);
	flood_fill(f, x, y - 1);
}

static int	check_remaining(char **map, int rows, int cols)
{
	int	i;
	int	j;

	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
			if (map[i][j] == 'C' || map[i][j] == 'E')
				return (0);
	}
	return (1);
}

int	ft_floodfill(t_data *data)
{
	char			**dup;
	t_flood_fill	f;
	int				ret;

	dup = dup_map(data->map, data->grid_rows);
	if (!dup)
		return (0);
	f.map = dup;
	f.rows = data->grid_rows;
	f.cols = data->grid_cols;
	flood_fill(&f, data->player_x, data->player_y);
	ret = check_remaining(dup, data->grid_rows, data->grid_cols);
	if (!ret)
		ft_printf("Error\nNo valid path\n");
	free_map(dup);
	return (ret);
}
