/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:05:48 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/03 18:44:23 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

	first_draw_minimap_player(&data); //draw and save in struct for moving arround.
	
	data.fovlines = mlx_new_image(data.mlx, 700, 400); //tmp for first run delete.
	mlx_image_to_window(data.mlx, data.fovlines, 0,0);
	draw_fov_line(&data);

	//new draw every movement thing -> broken.
	// data.layer1  = mlx_new_image(data.mlx, 700, 400);
	
	// start program // add mouse hook.
	mlx_loop_hook(data.mlx, &input_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);

	//end of program clean.
	// printf("does this trigger after mlx temrinate ? \n"); //-> yes
	clean_map_info(&data);
	clean_2dchar_array(&data, data.mapheight);
	return (0);
}
