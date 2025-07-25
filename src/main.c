/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:05:48 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/25 16:54:15 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// maybe put draw_hook into game_hook cause smol.
// limit fps here ?
void	draw_hook(void *param)
{
	t_vars *data;

	data = (t_vars *)param;
	draw_3d_view(data);
	draw_minimap(data);
	draw_image_outline(data->minimap, 0xE6E6FAFF); //moved for space reason.
}

// wrapper cause mlx takes 1 hook.
void	game_hook(void *param)
{
	t_vars *data;

	data = (t_vars *)param;
	input_hook(data);
	mlx_cursor_hook(data->mlx, mouse_hook, data);
	draw_hook(data); // draw minimap & draw 3d cast
}

int	main(int argc, char **argv)
{
	t_vars	data;

	if (argc != 2)
		return (ft_strerror("Give 1 map argument please."));
	if (start_mlx(&data) == 1)
		return (ft_strerror("Could not start mlx instance.\n"));
	if (import_mapfile(&data, argv[1]) == 1)
	{
		mlx_terminate(data.mlx);
		return (1);
	}
	mlx_loop_hook(data.mlx, &game_hook, &data);
	mlx_loop(data.mlx);

	//end of program clean.
	clean_textures(&data);
	clean_map_info(&data);
	clean_array(data.themap);
	mlx_terminate(data.mlx);
	return (0);
}
