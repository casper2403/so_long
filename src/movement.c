#include "so_long.h"

void	move_player(t_data *data, int dx, int dy)
{
	int	new_x;
	int	new_y;
	char	tile;
	static int	moves = 1;

	new_x = data->player_x + dx;
	new_y = data->player_y + dy;
	if (new_x < 0 || new_x >= data->grid_cols ||
		new_y < 0 || new_y >= data->grid_rows)
		return ;
	tile = data->map[new_y][new_x];
	if (tile == '0' || tile == 'C')
	{
		data->map[data->player_y][data->player_x] = '0';
		data->map[new_y][new_x] = 'P';
		data->player_x = new_x;
		data->player_y = new_y;
		mlx_clear_window(data->mlx, data->win);
		create_grid(data);
		ft_printf("Amount of moves: %d\n", moves++);
	}
}
