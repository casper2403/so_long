#include "../lib/mlx_linux/mlx.h"
#include "../lib/libft/libft.h"
#include <stdlib.h>

#define TILE_SIZE 64

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *tile_img;
    int     win_width;
    int     win_height;
    int     grid_cols;
    int     grid_rows;
}   t_data;

int init(t_data *data, int cols, int rows) {
    data->mlx = mlx_init();
    if (!data->mlx) return (0);
    data->grid_cols = cols;
    data->grid_rows = rows;
    data->win_width = cols * TILE_SIZE;
    data->win_height = rows * TILE_SIZE;
    data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "Tile Grid");
    if (!data->win) return (0);
    int img_width, img_height;
    data->tile_img = mlx_xpm_file_to_image(data->mlx, "assets/sprites/cave water stalagmite.xpm", &img_width, &img_height);
    if (!data->tile_img || img_width != TILE_SIZE || img_height != TILE_SIZE) {
        return (0);
    }
    return (1);
}

void create_grid(t_data *data) {
    int x, y;

    y = -1;
    while (++y < data->grid_rows) {
        x = -1;
        while (++x < data->grid_cols) {
            mlx_put_image_to_window(
                data->mlx, data->win, data->tile_img,
                x * TILE_SIZE,
                y * TILE_SIZE
            );
        }
    }
}

int main(int argc, char **argv) {
    t_data data;

    if (!init(&data, 20, 15)) {
        exit(1);
    }
    create_grid(&data);
    mlx_loop(data.mlx);
    return (0);
}
