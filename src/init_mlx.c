#include "header.h"

// set keystates to zero.
static void	set_keystate_struct(t_vars *data)
{
	data->keystate.w = 0;
	data->keystate.a = 0;
	data->keystate.s = 0;
	data->keystate.d = 0;
}

// save some space in main.
int	init_mlx_images(t_vars *data)
{
	data->view3d = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, data->view3d, 0, 0);

	data->minimapbg = mlx_new_image(data->mlx, 320, 320);
	mlx_image_to_window(data->mlx, data->minimapbg, WIDTH - 330, 10);
	fill_image_color(data->minimapbg, 160);
	
	data->minimap = mlx_new_image(data->mlx, 320, 320);
	mlx_image_to_window(data->mlx, data->minimap, WIDTH - 330, 10);

	return (0);
}

// start mlx save in data struct.
int	start_mlx(t_vars *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!data->mlx)
		return (1);
	init_mlx_images(data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	set_keystate_struct(data);
	return (0);
}
