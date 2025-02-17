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

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*tile_img;
	int		win_width;
	int		win_height;
	int		grid_cols;
	int		grid_rows;
}	t_data;

#endif
