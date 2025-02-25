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

int ft_floodfill(t_data *data)
{
    char    **dup;
    int     rows = data->grid_rows;
    int     i;
    int     j;

    dup = dup_map(data->map, rows);
    if (!dup)
        return (0);
    flood_fill(dup, data->player_x, data->player_y, rows, data->grid_cols);
    i = -1;
    while (++i < rows)
    {
        j = -1;
        while (++j < data->grid_cols)
        {
            if (dup[i][j] == 'C' || dup[i][j] == 'E')
            {
                int k = -1;
                while (++k < rows)
                    free(dup[k]);
                free(dup);
                ft_printf("Error\nNo valid path\n");
                return (0);
            }
        }
    }
    i = -1;
    while (dup[++i])
        free(dup[i]);
    free(dup);
    return (1);
}
