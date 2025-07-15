/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_small_minimap.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/09 17:09:25 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/15 17:16:40 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "holdmydata.h"

//  draw floors & walls based on distance to player
static void	draw_square(t_vars *data, float tilex, float tiley, uint32_t clr)
{
	t_things	vars;
	int			y;
	int			x;

	vars.frac_x = (float)modf(data->plx, &vars.ignore);
	vars.frac_y = (float)modf(data->ply, &vars.ignore);
	vars.dx = (tilex - data->plx) * MAPSCALE - vars.frac_x * MAPSCALE;
	vars.dy = (tiley - data->ply) * MAPSCALE - vars.frac_y * MAPSCALE;
	vars.drawx = (data->minimap->width / 2) + (int)vars.dx;
	vars.drawy = (data->minimap->height / 2) + (int)vars.dy;
	y = 0;
	while (y < MAPSCALE)
	{
		x = 0;
		while (x < MAPSCALE)
		{
			if (y == 0 || x == 0 || y == MAPSCALE - 1 || x == MAPSCALE - 1)
				set_pixel(data->minimap, vars.drawx + y, vars.drawy + x, clr);
			x++;
		}
		y++;
	}
}

// draw filled floors & walls based on distance to player.
static void	square_line(t_vars *data, float tilex, float tiley, uint32_t clr)
{
	t_things	vars;
	int			y;
	int			x;

	vars.frac_x = (float)modf(data->plx, &vars.ignore);
	vars.frac_y = (float)modf(data->ply, &vars.ignore);
	vars.dx = (tilex - data->plx) * MAPSCALE - vars.frac_x * MAPSCALE;
	vars.dy = (tiley - data->ply) * MAPSCALE - vars.frac_y * MAPSCALE;
	vars.drawx = (data->minimap->width / 2) + (int)vars.dx;
	vars.drawy = (data->minimap->height / 2) + (int)vars.dy;
	y = 0;
	while (y < MAPSCALE)
	{
		x = 0;
		while (x < MAPSCALE)
		{
			set_pixel(data->minimap, vars.drawx + y, vars.drawy + x, clr);
			x++;
		}
		y++;
	}
}

// change this out for new DDA logic.
// line 122:  || data->themap[map_y][map_x] == 'D' for doors
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

	line.x1 = data->minimap->width / 2;
	line.y1 = data->minimap->height / 2;

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
	line.x2 = data->minimap->width / 2 + (ray_x - data->plx) * MAPSCALE;
	line.y2 = data->minimap->height / 2 + (ray_y - data->ply) * MAPSCALE;
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
		bresenham_line(data->minimap, line, 0xFFFFFF);
		i++;
	}
}

//draw walls/floors arround player.
// else if (data->themap[map_y][map_x] == 'D')
// 	draw_filled_block(data, tile_x, tile_y, 0xFF0000FF);
void	draw_small_minimap(t_vars *data)
{
	int		offset_x;
	int		offset_y;
	float	tile_x;
	float	tile_y;
	int		map_x;
	int		map_y;

	clear_image(data->minimap);
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
					square_line(data, tile_x, tile_y, 0xFFFFFFFF);
				else if (data->themap[map_y][map_x] == '0')
					draw_square(data, tile_x, tile_y, 0xFFFFFF09);
			}
			offset_x++;
		}
		offset_y++;
	}
	draw_fov_minimap(data);
	// draw_image_outline(data->minimap, 0xE6E6FAFF);
}
