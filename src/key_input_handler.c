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

// maybe chang angle ammount.
void	change_player_angle(t_vars *data, int dir)
{
	if (dir == 1)
	{
		data->pla += 0.04;
		if (data->pla > (2 * PI))
			data->pla += (2 * PI);
	}
	else
	{
		data->pla -= 0.04;
		if (data->pla < 0)
			data->pla = (2 * PI);
	}
	data->pdx = cos(data->pla) * 5;
	data->pdy = sin(data->pla) * 5;
}

//todo: Find way to keep mouse in screen.
void mouse_hook(double xpos, double ypos, void *param)
{
	(void) ypos;
	(void) xpos;
	(void) param;

	t_vars			*data;
	static double	lastpos;

	data = (t_vars *)param;
	if (lastpos > xpos)
		change_player_angle(data, 0);
	if (lastpos < xpos)
		change_player_angle(data, 1);
	lastpos = xpos;
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2); // keep mouse in screen.
}



void	input_hook(void *param)
{
	t_vars	*data;

	data = (t_vars *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->plx += (data->pdx / 40);
		data->ply += (data->pdy / 40);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->plx -= (data->pdx / 40);
		data->ply -= (data->pdy / 40);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->plx += data->pdy / 60;
		data->ply += -data->pdx / 60;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->plx += -data->pdy / 60;
		data->ply += data->pdx / 60;
	}
	// - add arrows for angle - 
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		change_player_angle(data, 1);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		change_player_angle(data, 0);
	}
}

