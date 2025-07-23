/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 12:05:00 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/23 12:07:07 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "ray_caster.h"

void	init_structs(t_vars *data, t_raydir *dir, t_map *map, double angle)
{
	dir->x = cos(angle);
	dir->y = sin(angle);
	map->x = (int)data->plx;
	map->y = (int)data->ply;
}

void	init_step(t_vars *data, t_raydir *dir, t_map *map, t_step *step)
{
	step->delta_x = fabs(1.0 / dir->x);
	step->delta_y = fabs(1.0 / dir->y);
	if (dir->x < 0)
	{
		step->x = -1;
		step->side_x = (data->plx - map->x) * step->delta_x;
	}
	else
	{
		step->x = 1;
		step->side_x = (map->x + 1.0 - data->plx) * step->delta_x;
	}
	if (dir->y < 0)
	{
		step->y = -1;
		step->side_y = (data->ply - map->y) * step->delta_y;
	}
	else
	{
		step->y = 1;
		step->side_y = (map->y + 1.0 - data->ply) * step->delta_y;
	}
}

void	dda(t_vars *data, t_map *map, t_step *step)
{
	while (1)
	{
		if (step->side_x < step->side_y)
		{
			step->side_x += step->delta_x;
			map->x += step->x;
			map->side = 0;
		}
		else
		{
			step->side_y += step->delta_y;
			map->y += step->y;
			map->side = 1;
		}
		if (data->themap[map->y][map->x] == '1')
			break ;
	}
}

double	calc_dist(t_vars *data, t_map *map, t_step *step, t_raydir *dir)
{
	if (map->side == 0)
		return ((map->x - data->plx + (1 - step->x) / 2.0) / dir->x);
	else
		return ((map->y - data->ply + (1 - step->y) / 2.0) / dir->y);
}

t_ray	build_ray(t_vars *data, t_raydir *dir, t_map *map, double dist)
{
	t_ray	ray;

	ray.hit_x = map->x;
	ray.hit_y = map->y;
	ray.side = map->side;
	ray.distance = dist;
	ray.line.x1 = (int)(data->plx * 32);
	ray.line.y1 = (int)(data->ply * 32);
	ray.line.x2 = (int)((data->plx + dir->x * dist) * 32);
	ray.line.y2 = (int)((data->ply + dir->y * dist) * 32);
	return (ray);
}
