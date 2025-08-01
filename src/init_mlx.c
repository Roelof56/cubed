/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 15:24:59 by jilustre      #+#    #+#                 */
/*   Updated: 2025/08/01 12:17:34 by roelof        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// save texture locations and color info.
static int	create_2d_char_array(t_vars *data)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(6 * sizeof(char *));
	if (!new)
		return (1);
	while (i < 6)
	{
		new[i] = NULL;
		i++;
	}
	data->map_info = new;
	return (0);
}

int	set_mapinfo_array(t_vars *data)
{
	int	i;

	i = 0;
	if (create_2d_char_array(data) == 1)
		return (1);
	while (i < 6)
	{
		data->map_info[i] = malloc(1 * sizeof(char));
		if (!data->map_info[i])
		{
			clean_array(data->map_info);
			return (1);
		}
		data->map_info[i][0] = '\0';
		i++;
	}
	return (0);
}

// save some space in main.
static int	init_mlx_images(t_vars *data)
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
	ft_bzero(data, sizeof(t_vars));
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", false);
	if (!data->mlx)
		return (1);
	if (init_mlx_images(data) == 1)
		return (1);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	if (set_mapinfo_array(data) == 1)
	{
		mlx_delete_image(data->mlx, data->view3d);
		mlx_delete_image(data->mlx, data->minimapbg);
		mlx_delete_image(data->mlx, data->minimap);
		return (1);
	}
	return (0);
}
