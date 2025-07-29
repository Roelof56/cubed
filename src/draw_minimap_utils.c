/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 15:19:02 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/29 09:40:02 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "draw_structs.h"
#include "ray_caster.h"

//  draw floors & walls based on distance to player
void	draw_square(t_vars *data, float tilex, float tiley, uint32_t clr)
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
void	square_line(t_vars *data, float tilex, float tiley, uint32_t clr)
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

// Outline img -> tmp for placement in window
void	draw_image_outline(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	while (x < img->width)
	{
		mlx_put_pixel(img, x, 0, color);
		mlx_put_pixel(img, x, img->height - 1, color);
		x++;
	}
	y = 1;
	while (y < img->height - 1)
	{
		mlx_put_pixel(img, 0, y, color);
		mlx_put_pixel(img, img->width - 1, y, color);
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

void	draw_single_fov_line(t_vars *data, double angle)
{
	t_line	line;

	angle = normalize_angle(angle);
	line = get_fov_line(data, angle);
	bresenham_line(data->minimap, line, 0xFFFFFF);
}
