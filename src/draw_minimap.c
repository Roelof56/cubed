#include "cubed.h"

// fill all edges of square.
// static void	draw_edge_minimap(mlx_image_t *image, t_color color)
// {
// 	u_int32_t	x;
// 	u_int32_t	y;

// 	y = 0;
// 	while (y < image->height)
// 	{
// 		x = 0;
// 		while (x < image->width)
// 		{
// 			//top and bottom
// 			if (y == 0 || y == image->height - 1)
// 			{
// 				image->pixels[(y * image->width + x) * 4] = color.r;
// 				image->pixels[(y * image->width + x) * 4 + 1] = color.g;
// 				image->pixels[(y * image->width + x) * 4 + 2] = color.b;
// 				image->pixels[(y * image->width + x) * 4 + 3] = color.a;	
// 			}
// 			//links & rechts
// 			else if (x == 0 || x == image->width - 1)
// 			{
// 				image->pixels[(y * image->width + x) * 4] = color.r;
// 				image->pixels[(y * image->width + x) * 4 + 1] = color.g;
// 				image->pixels[(y * image->width + x) * 4 + 2] = color.b;
// 				image->pixels[(y * image->width + x) * 4 + 3] = color.a;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

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
	printf("\n");
}

static int	is_player_identifier(char c)
{
	if (c == 'N' || c == 'S')
		return (0);
	if (c == 'E' || c == 'W')
		return (0);
	return (1);
}

void	mm_player_img_loc_change(t_vars *vars)
{
	int xpos;
	int ypos;

	xpos = (vars->pl_x * 32);
	ypos = (vars->pl_y * 32);
	vars->td_player->instances[0].x = xpos;
	vars->td_player->instances[0].y = ypos;
}


int	draw_minimap(t_vars *vars)
{
	int			i;
	int			j;
	mlx_image_t	*rectangle;

	i = 0;
	j = 0;
	rectangle = NULL;
	// rectangle = mlx_new_image(vars->mlx, 400, 200); //og
	rectangle = mlx_new_image(vars->mlx, 700, 400); 
	if (!rectangle)
		return (-1); //return some error func.
	// draw_edge_minimap(rectangle, vars->ceiling_color); //nu onderaan func.
	while (vars->themap[i])
	{
		while (vars->themap[i][j])
		{
			if (vars->themap[i][j] == '1')
			{
				mm_draw_wall(j, i, rectangle, vars->ceiling_color); //j = x
			}
			if (is_player_identifier(vars->themap[i][j]) == 0)
			{
				draw_minimap_player(vars);
			}
			j++;
		}
		j = 0;
		i++;	
	}
	mlx_image_to_window(vars->mlx, rectangle, 0, 0);
	return (0);
}

// og minimap
// int	draw_minimap(t_vars *vars)
// {
// 	int			i;
// 	int			j;
// 	mlx_image_t	*rectangle;

// 	i = 0;
// 	j = 0;
// 	rectangle = NULL;
// 	rectangle = mlx_new_image(vars->mlx, 32, 32);
// 	draw_rectangle(rectangle, vars->ceiling_color);
// 	while (vars->themap[i])
// 	{
// 		while (vars->themap[i][j])
// 		{
// 			if (vars->themap[i][j] == '1')
// 				mlx_image_to_window(vars->mlx, rectangle, (j * 32), (i * 32));
// 			if (is_player_identifier(vars->themap[i][j]) == 0)
// 				draw_minimap_player(vars);
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// 	return (0);
// }
