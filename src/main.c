/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:05:48 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/15 21:23:41 by roelof        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <sys/time.h>

void	look_at_my_fps(t_vars *data)
{
	gettimeofday(&data->time_now, NULL);

	long sec = data->time_now.tv_sec - data->time_prev.tv_sec;
	long usec = data->time_now.tv_usec - data->time_prev.tv_usec;
	data->deltatime = sec + usec / 1000000.0;

	if (data->deltatime > 0)
		data->fps = 1.0 / data->deltatime;

	data->time_prev = data->time_now;
	data->time_accum += data->deltatime;
	data->frame_count++;
	if (data->time_accum >= 1.0)
	{
		data->fps = data->frame_count / data->time_accum;
		printf("FPS: %.1f\n", data->fps);
		data->frame_count = 0;
		data->time_accum = 0.0;
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
	gettimeofday(&data.time_prev, NULL);
	
	mlx_loop_hook(data.mlx, &game_hook, &data);
	mlx_loop(data.mlx);

	//end of program clean.
	mlx_terminate(data.mlx);
	clean_map_info(&data);
	clean_2dchar_array(&data, data.mapheight);
	return (0);
}
