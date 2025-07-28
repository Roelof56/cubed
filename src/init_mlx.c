/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 15:24:59 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/28 19:13:41 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// save some space in main.
int	init_mlx_images(t_vars *data)
{
	data->view3d = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->view3d)
		return (1);
	mlx_image_to_window(data->mlx, data->view3d, 0, 0);
	data->minimapbg = mlx_new_image(data->mlx, 320, 320);
	if (!data->minimapbg)
	{
		mlx_delete_image(data->mlx, data->view3d);
		return (1);
	}
	mlx_image_to_window(data->mlx, data->minimapbg, WIDTH - 330, 10);
	fill_image_color(data->minimapbg, 160);
	data->minimap = mlx_new_image(data->mlx, 320, 320);
	if (!data->minimap)
	{
		mlx_delete_image(data->mlx, data->view3d);
		mlx_delete_image(data->mlx, data->minimapbg);
		return (1);
	}
	mlx_image_to_window(data->mlx, data->minimap, WIDTH - 330, 10);
	return (0);
}

// start mlx save in data struct.
int	start_mlx(t_vars *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", false);
	if (!data->mlx)
		return (1);
	if (init_mlx_images(data) == 1)
		return (1);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	return (0);
}
