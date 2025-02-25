#include "so_long.h"

void	free_map(char **map)
{
    int	i;

    if (!map)
        return ;
    i = -1;
    while (map[++i])
        free(map[i]);
    free(map);
}

void	clean_resources(t_data *data)
{
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->wall_img)
        mlx_destroy_image(data->mlx, data->wall_img);
    if (data->player_img)
        mlx_destroy_image(data->mlx, data->player_img);
    if (data->tile_img)
        mlx_destroy_image(data->mlx, data->tile_img);
    if (data->collectible_img)
        mlx_destroy_image(data->mlx, data->collectible_img);
    if (data->exit_img)
        mlx_destroy_image(data->mlx, data->exit_img);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    free_map(data->map);
}
