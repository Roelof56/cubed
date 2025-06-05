#include "header.h"

void	move_minimap_player(t_vars *vars)
{
	int xpos;
	int ypos;

	xpos = (vars->plx * 32);
	ypos = (vars->ply * 32);
	vars->mmpl->instances[0].x = xpos;
	vars->mmpl->instances[0].y = ypos;
}

void	first_draw_minimap_player(t_vars *data)
{
	int newx;
	int newy;
	int scale = 32; //make define

	newx = (int)data->plx * scale;
	newy = (int)data->ply * scale;

	data->pdx = cos(data->pla) * 5;
	data->pdy = sin(data->pla) * 5;


	data->mmpl = NULL;
	data->mmpl  = mlx_new_image(data->mlx, 8, 8);
	if (!data->mmpl)
	{
		printf("big old error\n");
		return ;
	}

	int i;
	int j;
	i = 0; 
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			mlx_put_pixel(data->mmpl, j, i, 0xFF00FF);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, data->mmpl, newx, newy);
	return ;
}
