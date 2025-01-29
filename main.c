#include <mlx.h>
#include <stdlib.h>

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*tile_img;
	int		scale;
	int		tile_size;
	int		grid_w;
	int		grid_h;
}   t_data;

void scale_image(t_data *d, void *img)
{
	int		bp[3];
	char	*o = mlx_get_data_addr(img, bp, bp + 1, bp + 2);
	void	*s = mlx_new_image(d->mlx, 8 * d->scale, 8 * d->scale);
	char	*n = mlx_get_data_addr(s, (int[1]){0}, (int[1]){0}, (int[1]){0});
	char	*src;

	for (int y=0; y<64; y++) {
		*src = (o + (y / 8 * bp[1]) + (y % 8 * bp[0] / 8));
		for (int dy = 0; dy < d->scale; dy++)
			for (int dx = 0; dx < d->scale; dx++)
				for (int i = 0; i < bp[0] / 8; i++)
					n[((y / 8 * d->scale + dy) * 8 * d->scale + y % 8 * d->scale + dx) * bp[0] / 8 + i]
						= src[i];
	}
	d->tile_img = s;
}

void init(t_data *data, int grid_w, int grid_h, int scale)
{
	void	*original_img;
	int		orig_w = 8, orig_h = 8;

	data->scale = scale;
	data->tile_size = 8 * scale;
	data->grid_w = grid_w;
	data->grid_h = grid_h;
	data->mlx = mlx_init();
	original_img = mlx_xpm_file_to_image(data->mlx, "tile.xpm", &orig_w, &orig_h);
	scale_image(data, original_img);
	data->win = mlx_new_window(data->mlx,
							data->grid_w * data->tile_size,
							data->grid_h * data->tile_size,
							"Scaled Grid");
	mlx_destroy_image(data->mlx, original_img);
}

void    create_grid(t_data *data)
{
	for (int y = 0; y < data->grid_h; y++)
		for (int x = 0; x < data->grid_w; x++)
			mlx_put_image_to_window(data->mlx, data->win, data->tile_img,
				x * data->tile_size,
				y * data->tile_size);
}

int main()
{
	t_data	data;

	init(&data, 20, 15, 20);
	create_grid(&data);
	mlx_loop(data.mlx);
}
