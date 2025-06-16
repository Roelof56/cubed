/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:05:48 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/16 14:59:28 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_hook(void *param)
{
	t_vars *data;

	data = (t_vars *)param;
	draw_fov_line(data);
	// limit fps here ?
}

void	game_hook(void *param)
{
	t_vars *data;

	data = (t_vars *)param;
	input_hook(data); // handle keyboard input.
	mlx_cursor_hook(data->mlx, mouse_hook, data); // hook that mouse
	draw_hook(data); // draw minimap & draw 3d cast
}


int	main(int argc, char **argv)
{
	t_vars	data;

	if (argc != 2)
		return (ft_strerror("Error\nGive 1 map argument please."));
	if (import_mapfile(&data, argv[1]) == 1)
		return (1);
	if (start_mlx(&data) == 1)
		return (ft_strerror("Error\nCould not start mlx instance.\n"));
	
	draw_minimap(&data); //only walls
	
	data.fovlines = mlx_new_image(data.mlx, 700, 400); //tmp for first run delete.
	mlx_image_to_window(data.mlx, data.fovlines, 0,0);
	draw_fov_line(&data);

	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(data.mlx, &game_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);

	//end of program clean.
	clean_map_info(&data);
	clean_2dchar_array(&data, data.mapheight);
	return (0);
}
