/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:05:48 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/31 21:00:41 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "ray_caster.h"

// wrapper cause mlx takes 1 hook.
void	game_hook(void *param)
{
	t_vars	*data;

	data = (t_vars *)param;
	input_hook(data);
	mlx_cursor_hook(data->mlx, mouse_hook, data);
	draw_3d_view(data);
	draw_minimap(data);
}

int	main(int argc, char **argv)
{
	t_vars	data;

	ft_bzero(&data, sizeof(t_vars));
	if (argc != 2)
	{
		printf("Error\nGive 1 map argument.\n");
		return (1);
	}
	if (start_mlx(&data) == 1)
	{
		printf("Error\nCould not start mlx instance\n");
		return (1);
	}
	if (import_mapfile(&data, argv[1]) == 1)
	{
		mlx_terminate(data.mlx);
		return (1);
	}
	mlx_loop_hook(data.mlx, &game_hook, &data);
	mlx_loop(data.mlx);
	clean_textures(&data);
	clean_map_info(&data);
	clean_array(data.themap);
	mlx_terminate(data.mlx);
	return (0);
}
