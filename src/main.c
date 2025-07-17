/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:05:48 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/17 16:34:04 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <sys/time.h>



static void	look_at_my_fps(t_vars *data)
{	
	gettimeofday(&data->fpsdata.time_now, NULL);

	long sec = data->fpsdata.time_now.tv_sec - data->fpsdata.time_prev.tv_sec;
	long usec = data->fpsdata.time_now.tv_usec - data->fpsdata.time_prev.tv_usec;
	data->fpsdata.deltatime = sec + usec / 1000000.0;

	if (data->fpsdata.deltatime > 0)
		data->fpsdata.fps = 1.0 / data->fpsdata.deltatime;

	data->fpsdata.time_prev = data->fpsdata.time_now;
	data->fpsdata.time_accum += data->fpsdata.deltatime;
	data->fpsdata.frame_count++;
	if (data->fpsdata.time_accum >= 1.0)
	{
		data->fpsdata.fps = data->fpsdata.frame_count / data->fpsdata.time_accum;
		printf("FPS: %.1f\n", data->fpsdata.fps);
		data->fpsdata.frame_count = 0;
		data->fpsdata.time_accum = 0.0;
	}
}

// maybe put draw_hook into game_hook cause smol.
// limit fps here ?
void	draw_hook(void *param)
{
	t_vars *data;

	data = (t_vars *)param;
	draw_3d_view(data); // turn off for doubling fps - test minimap
	draw_small_minimap(data);
	look_at_my_fps(data);
}

/* look at that game hook */
void	game_hook(void *param)
{
	t_vars *data;

	data = (t_vars *)param;
	input_hook(data);
	// mlx_cursor_hook(data->mlx, mouse_hook, data);
	draw_hook(data);
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

	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN); // move to init func
	gettimeofday(&data.fpsdata.time_prev, NULL);
	
	mlx_loop_hook(data.mlx, &game_hook, &data);
	mlx_loop(data.mlx);

	//end of program clean.
	mlx_terminate(data.mlx);
	clean_map_info(&data);
	clean_2dchar_array(&data, data.mapheight);
	return (0);
}
