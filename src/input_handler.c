#include "cubed.h"

// maybe chang angle ammount.
void	change_player_angle(t_vars *vars, int dir)
{
	if (dir == 1)
	{
		vars->pl_angle += 2;
		if (vars->pl_angle > 360)
			vars->pl_angle = 0;
	}
	else
	{
		vars->pl_angle -= 2;
		if (vars->pl_angle < 0.1)
			vars->pl_angle = 359.99;
	}
}

// static void debug_printer(t_vars *vars)
// {
// 	printf("x: %f\n", vars->pl_x);
// 	printf("y: %f\n", vars->pl_y);
// }

static int check_for_wall(t_vars *vars)
{
	// char	type;
	int		newx;
	int		newy;

	// type = 'a';
	newx = floor(vars->pl_x);
	newy = floor(vars->pl_y);

	if (newx > 0 && newy > 0) //check voor max ?
	{
		printf("type: %c\n", vars->themap[newy][newx]);
		// type = vars->themap[newy][newx];
		// printf("type: %c", type);
	}
	// if (vars->themap[newy][newx] == wall)
	// 	return (1);
	return (0);
}

void	input_hook(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
			vars->pl_y -= 0.1;
			if (check_for_wall(vars) == 1)
				vars->pl_y += 0.1;
			else
				mm_player_img_loc_change(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
			vars->pl_y += 0.1;
			if (check_for_wall(vars) == 1)
				vars->pl_y -= 0.1;
			else
				mm_player_img_loc_change(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
			vars->pl_x -= 0.1;
			if (check_for_wall(vars) == 1)
				vars->pl_x += 0.1;
			else
				mm_player_img_loc_change(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
			vars->pl_x += 0.1;
			if (check_for_wall(vars) == 1)
				vars->pl_x -= 0.1;
			else
				mm_player_img_loc_change(vars);
	}
	// - add arrows for angle - 
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		change_player_angle(vars, 1);
		draw_minimap_player(vars);
	}
	else if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		change_player_angle(vars, 0);
		draw_minimap_player(vars);
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
}
