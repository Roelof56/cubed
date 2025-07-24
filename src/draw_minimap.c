/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/09 17:09:25 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/24 14:57:08 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "holdmydata.h"
#include "ray_caster.h"

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

static t_line	get_fov_line(t_vars *data, double angle)
{
	t_line	line;
	t_ray	ray;
	double	dx;
	double	dy;

	ray = ray_wall(data, angle);
	line.x1 = data->minimap->width / 2;
	line.y1 = data->minimap->height / 2;
	dx = ray.wall_hit_x - data->plx;
	dy = ray.wall_hit_y - data->ply;
	line.x2 = line.x1 + dx * MAPSCALE;
	line.y2 = line.y1 + dy * MAPSCALE;
	return (line);
}

//draw fovlines. maybe use 1 degree to rad as step ? 
void	draw_fov_minimap(t_vars *data)
{
	int		num_rays;
	double	fov;
	double	start_angle;
	double	step;
	int		i;
	double	angle;
	t_line	line;

	num_rays = 60;
	fov = PI / 3.0;
	start_angle = data->pla - fov / 2.0;
	step = fov / num_rays;
	i = 0;
	while (i < num_rays)
	{
		angle = normalize_angle(start_angle + i * step);
		line = get_fov_line(data, angle);
		bresenham_line(data->minimap, line, 0xFFFFFF);
		i++;
	}
}

//set draw_minimap_vars - norm made me do it.
static void	set_draw_minimap_vars(t_mmdata *mmdata, float plx, float ply)
{
	mmdata->tilex = plx + mmdata->offsetx;
	mmdata->tiley = ply + mmdata->offsety;
	mmdata->mapx = (int)floorf(mmdata->tilex);
	mmdata->mapy = (int)floorf(mmdata->tiley);
}

// new - use struct.
void	draw_minimap(t_vars *data)
{
	t_mmdata	mmdata;

	clear_image(data->minimap);
	mmdata.offsety = -VIEW;
	while (mmdata.offsety <= VIEW)
	{
		mmdata.offsetx = -VIEW;
		while (mmdata.offsetx <= VIEW)
		{
			set_draw_minimap_vars(&mmdata, data->plx, data->ply);
			if (mmdata.mapx >= 0 && mmdata.mapx < data->mapwidth && mmdata.mapy >= 0 && mmdata.mapy < data->mapheight)
			{
				if (data->themap[mmdata.mapy][mmdata.mapx] == '1')
					square_line(data, mmdata.tilex, mmdata.tiley, 0xFFFFFFFF);
				else if (data->themap[mmdata.mapy][mmdata.mapx] == '0')
					draw_square(data, mmdata.tilex, mmdata.tiley, 0xFFFFFF09);
			}
			mmdata.offsetx++;
		}
		mmdata.offsety++;
	}
	draw_fov_minimap(data);
}
