#include "header.h"

// first attempt @ redrawing entire minimap - now it's just player. very wonky
void	draw_mm_new(t_vars *data)
{
	int newx;
	int newy;

	newx = (int)data->plx * SCALE;
	newy = (int)data->ply * SCALE;

	data->pdx = cos(data->pla) * 5;
	data->pdy = sin(data->pla) * 5;


	mlx_delete_image(data->mlx, data->layer1);
	data->layer1  = mlx_new_image(data->mlx, 700, 400);
	if (!data->layer1)
	{
		printf("big old error\n");
		return ;
	}
	// draw player
	int i;
	int j;
	i = newy;
	while (i < (newy + 8))
	{
		j = newx;
		while (j < (newx + 8))
		{
			mlx_put_pixel(data->layer1, j, i, 0xFF00FF);
			j++;
		}
		i++;
	}
	// draw direction line


	// to the screen it goes
	mlx_image_to_window(data->mlx, data->layer1, 0, 0);
	return ;
}