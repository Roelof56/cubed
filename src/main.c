/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:05:48 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/09 15:39:00 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// maybe put draw_hook into game_hook cause smol.
void	draw_hook(void *param)
{
	t_vars *data;

	data = (t_vars *)param;

	draw_3d_view(data);
	draw_small_minimap(data);
	// limit fps here ?
}

void	game_hook(void *param)
{
	t_vars *data;

	data = (t_vars *)param;
	input_hook(data); // handle keyboard input.
	// mlx_cursor_hook(data->mlx, mouse_hook, data); // hook that mouse
	draw_hook(data); // draw minimap & draw 3d cast
}

int	main(int argc, char **argv)
{
	t_vars	data;

	if (argc != 2)
		return (ft_strerror("Error\nGive 1 map argument please."));
	if (start_mlx(&data) == 1) //changed order with import_mapfile
		return (ft_strerror("Error\nCould not start mlx instance.\n"));
	if (import_mapfile(&data, argv[1]) == 1) //maybe neat close mlx on error in here.
		return (1);
	
	data.view3d = mlx_new_image(data.mlx, 700, 400);
	mlx_image_to_window(data.mlx, data.view3d, 0, 400);

	data.layer1 = mlx_new_image(data.mlx, 320, 320); // new small minimap
	mlx_image_to_window(data.mlx, data.layer1, WIDTH - 320, 0); // place left of og map

	/* testing color import. */
	data.layer2 = mlx_new_image(data.mlx, 320, 320);
	mlx_image_to_window(data.mlx, data.layer2, 0, 0);
	fill_image_color(data.layer2, ft_get_rgba(data.textures.c));
	/* end color test.*/

	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN); // move to init func
	mlx_loop_hook(data.mlx, &game_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);

	//end of program clean.
	clean_map_info(&data);
	clean_2dchar_array(&data, data.mapheight);
	return (0);
}

