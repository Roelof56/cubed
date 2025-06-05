#include "header.h"

// OLD -> weird offset cause of floor() ? 
// static int check_for_wall(t_vars *vars) 
// {
// 	// char	type;
// 	int		newx;
// 	int		newy;

// 	// type = 'a'; 
// 	newx = floor(vars->pl_x);
// 	newy = floor(vars->pl_y);

// 	if (newx > 0 && newy > 0) //check voor max ?
// 	{
// 		printf("type: %c\n", vars->themap[newy][newx]);
// 		// type = vars->themap[newy][newx];
// 		// printf("type: %c", type);
// 	}
// 	// if (vars->themap[newy][newx] == wall)
// 	// 	return (1);
// 	return (0);
// }


// maybe chang angle ammount. // OLD
void	change_player_angle(t_vars *data, int dir)
{
	if (dir == 1)
	{
		data->pla += 0.05;
		if (data->pla > (2 * PI))
			data->pla = 0;
	}
	else
	{
		data->pla -= 0.05;
		if (data->pla < 0)
			data->pla = (2 * PI);
	}
	data->pdx = cos(data->pla) * 5;
	data->pdy = sin(data->pla) * 5;
	// printf("pdx: %f\n", data->pdx);
	// printf("pdy: %f\n", data->pdy);
}

void	input_hook(void *param)
{
	t_vars	*data;

	data = (t_vars *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		// printf("plx: %f\n", data->plx);
		// printf("ply: %f\n", data->ply);
		// printf("pdx: %f\n", data->pdx);
		// printf("pdy: %f\n", data->pdy);y
		data->plx += (data->pdx / 20);
		data->ply += (data->pdy / 20);
		move_minimap_player(data);
		draw_fov_line(data);

	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->plx -= (data->pdx / 20);
		data->ply -= (data->pdy / 20);
		move_minimap_player(data);
		draw_fov_line(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->plx -= 0.1;
		move_minimap_player(data);
		draw_fov_line(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->plx += 0.1;
		move_minimap_player(data);
		draw_fov_line(data);
	}
	// - add arrows for angle - 
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		change_player_angle(data, 1);
		draw_fov_line(data);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		change_player_angle(data, 0);
		draw_fov_line(data);
	}
}

// - test keys -
// if (mlx_is_key_down(vars->mlx, MLX_KEY_P)) // 'P' change img color
// {
// 	// change_img_to_color(vars->square, vars->ceiling_color);
// 	printf("P testkey be empty.\n");
// }
// if (mlx_is_key_down(vars->mlx, MLX_KEY_L)) // 'L' -> draw minimap
// {
// 	printf("L testkey = empty.\n");
// }

