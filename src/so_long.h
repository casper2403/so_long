/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstevens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:29:28 by cstevens          #+#    #+#             */
/*   Updated: 2025/02/17 15:29:32 by cstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 64

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/keysym.h>
# include "../lib/mlx_linux/mlx.h"
# include "../lib/libft/libft.h"

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*wall_img;
	void	*player_img;
	void	*tile_img;
	void	*collectible_img;
	void	*exit_img;
	int		win_width;
	int		win_height;
	int		grid_cols;
	int		grid_rows;
	int		player_x;
	int		player_y;
	char	**map;
}	t_data;

int	ft_floodfill(t_data *data);
void	move_player(t_data *data, int dx, int dy);
int	create_grid(t_data *data);
int	ft_mapcheck(t_data *data);
void	clean_resources(t_data *data);
void	free_map(char **map);

#endif
