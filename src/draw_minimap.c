#include "header.h"

static void mm_draw_wall(int x, int y, mlx_image_t *img, t_color color)
{
	int	i;
	int clr;
	int newx;
	int newy;
	int	scale = 32; //Make define ?

	i = 0;
	newx = x * scale;
	newy = y * scale;
	clr = ft_get_rgba(color.r, color.g, color.b, color.a);
	while (i < scale)
	{
		mlx_put_pixel(img, (newx + i), newy, clr);
		mlx_put_pixel(img, (newx + i), (newy + scale), clr);
		i++;
	}
	i = 0;
	while (i < scale)
	{
		mlx_put_pixel(img, newx, (newy + i), clr);
		mlx_put_pixel(img, (newx + scale), (newy + i), clr);
		i++;
	}
}

int	draw_minimap(t_vars *data)
{
	int			i;
	int			j;
	mlx_image_t	*layer0;

	t_color		tmp;
	tmp.r = 250;
	tmp.g = 10;
	tmp.b = 0;
	tmp.a = 250;

	i = 0;
	j = 0;
	layer0 = NULL;
	layer0 = mlx_new_image(data->mlx, 700, 400);
	if (!layer0)
	{
		printf("big old error\n");
		return (-1); //return some error func.
	}
	while (data->themap[i])
	{
		while (data->themap[i][j])
		{
			if (data->themap[i][j] == '1')
			{
				mm_draw_wall(j, i, layer0, tmp);
			}
			j++;
		}
		j = 0;
		i++;	
	}
	mlx_image_to_window(data->mlx, layer0, 0, 0);
	return (0);
}
