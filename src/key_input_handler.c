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
}

//todo: Find way to keep mouse in screen.
void mouse_hook(double xpos, double ypos, void *param)
{
	(void) ypos;
	(void) xpos;
	(void) param;

	// t_vars *data;
	// static double lastpos;

	// data = (t_vars *)param;
	// if (lastpos > xpos)
	// 	printf("moving left\n");
	// if (lastpos < xpos)
	// 	printf("moving right\n");
	// lastpos = xpos;
	// mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
	// printf("Mouse moved: %.2f\n", xpos);
	// printf("%f", data->pla);
}



void	input_hook(void *param)
{
	t_vars	*data;

	data = (t_vars *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->plx += (data->pdx / 20);
		data->ply += (data->pdy / 20);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->plx -= (data->pdx / 20);
		data->ply -= (data->pdy / 20);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->plx -= 0.1; //add 'strafe' ?
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->plx += 0.1; //add 'strafe' ?
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

