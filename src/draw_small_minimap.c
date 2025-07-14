/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_small_minimap.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/09 17:09:25 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/09 17:09:27 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// draw floors & walls based on distance to player.
// todo: make outer 2 blocks more transparent last 2 characters of hex code.
static void draw_block(t_vars *data, float tilex, float tiley, uint32_t color)
{
	int i;
	int j;

	float frac_x;
	float frac_y;
	double ignore; // needed for modf for some reason...

	// rest of float 5.7 = 0.7
	frac_x = (float)modf(data->plx, &ignore); // move to draw-small-minimap
	frac_y = (float)modf(data->ply, &ignore); // cause this is heavy computing for no reason

	// world-space to minimap-pixel, // I swear i'll make this norminette approved.
	float dx = (tilex - data->plx) * MAPSCALE - frac_x * MAPSCALE;
	float dy = (tiley - data->ply) * MAPSCALE - frac_y * MAPSCALE;

	// screen center // this can just be in drawx. wich makes it a lil unreadable.
	int centerx = data->layer1->width / 2;
	int centery = data->layer1->height / 2;

	uint32_t drawx = centerx + (int)dx; // maybe create a struct & setter function.
	uint32_t drawy = centery + (int)dy;	// for this & all needed shit above.

	// actual drawing of block lines
	i = 0;
	while (i < MAPSCALE)
	{
		j = 0;
		while (j < MAPSCALE)
		{
			if (i == 0 || j == 0 || i == MAPSCALE - 2 || j == MAPSCALE - 2)
			{
				if (drawx + i >= 0 && drawx + i < data->layer1->width &&
					drawy + j >= 0 && drawy + j < data->layer1->height)
					mlx_put_pixel(data->layer1, drawx + i, drawy + j, color);
			}
			j++;
		}
		i++;
	}
}

// change this out for new DDA logic.
static t_line get_line_coordinates(t_vars *data, double angle)
{
	t_line	line;

	double	ray_x = data->plx;
	double	ray_y = data->ply;

	double	dx = cos(angle);
	double	dy = sin(angle);
	double	step = 0.05;
	int		map_x; 
	int		map_y;
	double	distance = 0;

	line.x1 = data->layer1->width / 2; // change to img center where player is.
	line.y1 = data->layer1->height / 2;

	while (distance < VIEW + 5)
	{
		ray_x += dx * step;
		ray_y += dy * step;
		map_x = (int)(ray_x);
		map_y = (int)(ray_y);
		distance += step;
		if (data->themap[map_y][map_x] == '1')
			break;
	}

	// add middle-player-position offset to endpoints ? - yes
	line.x2 = data->layer1->width / 2 + (ray_x - data->plx) * MAPSCALE;
	line.y2 = data->layer1->height / 2 + (ray_y - data->ply) * MAPSCALE;

	return (line);
}

//draw fovlines. maybe use 1 degree to rad as step ? 
void	draw_fov_minimap(t_vars *data)
{
	const int num_rays = 60;  // number of rays
	const double fov = PI / 3;  // 60 degrees field of view
	const double start_angle = data->pla - fov / 2;
	const double step = fov / num_rays;
	int	i = 0;
	t_line line;

	while (i < num_rays)
	{
		double angle = start_angle + i * step;
		line = get_line_coordinates(data, angle);
		bresenham_line(data->layer1, line, 0xFFFFFF);
		i++;
	}
}


//draw walls/floors arround player.
void	draw_small_minimap(t_vars *data)
{
	int		offset_x;
	int		offset_y;
	float	tile_x;
	float	tile_y;
	int		map_x;
	int		map_y;

	clear_image(data->layer1);
	offset_y = -VIEW;
	while (offset_y <= VIEW)
	{
		offset_x = -VIEW;
		while (offset_x <= VIEW)
		{
			tile_x = data->plx + offset_x;
			tile_y = data->ply + offset_y;

			map_x = (int)floorf(tile_x);
			map_y = (int)floorf(tile_y);

			if (map_x >= 0 && map_x < data->mapwidth && map_y >= 0 && map_y < data->mapheight)
			{
				if (data->themap[map_y][map_x] == '1')
					draw_block(data, tile_x, tile_y, 0xFF0000FF);
				else if (data->themap[map_y][map_x] == '0')
					draw_block(data, tile_x, tile_y, 0x87CEEB12);
			}
			offset_x++;
		}
		offset_y++;
	}
	draw_fov_minimap(data);
	draw_image_outline(data->layer1, 0xE6E6FAFF);
}
