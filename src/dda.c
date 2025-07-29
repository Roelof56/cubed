/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 12:05:00 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/29 09:50:07 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "ray_caster.h"

/*Sets ray direction vector and start tile*/
void	init_ray(t_vars *data, t_raydir *dir, t_map *map, double angle)
{
	dir->x = cos(angle);
	dir->y = sin(angle);
	map->map_x = (int)data->plx;
	map->map_y = (int)data->ply;
}

/*Prepares step direction and side distances for DDA to travers map*/
void	ini_step(t_vars *data, t_raydir *dir, t_map *map, t_step *step)
{
	step->delta_x = fabs(1.0 / dir->x);
	step->delta_y = fabs(1.0 / dir->y);
	if (dir->x < 0)
	{
		step->step_x = -1;
		step->side_dist_x = (data->plx - map->map_x) * step->delta_x;
	}
	else
	{
		step->step_x = 1;
		step->side_dist_x = (map->map_x + 1.0 - data->plx) * step->delta_x;
	}
	if (dir->y < 0)
	{
		step->step_y = -1;
		step->side_dist_y = (data->ply - map->map_y) * step->delta_y;
	}
	else
	{
		step->step_y = 1;
		step->side_dist_y = (map->map_y + 1.0 - data->ply) * step->delta_y;
	}
}

/*Performs the DDA algorithm to walk the ray through the grid*/
void	dda(t_vars *data, t_map *map, t_step *step)
{
	while (1)
	{
		if (step->side_dist_x < step->side_dist_y)
		{
			step->side_dist_x += step->delta_x;
			map->map_x += step->step_x;
			map->side = 0;
		}
		else
		{
			step->side_dist_y += step->delta_y;
			map->map_y += step->step_y;
			map->side = 1;
		}
		if (data->themap[map->map_y][map->map_x] == '1')
			break ;
	}
}

/*Calculates the exact distance from the player to the wall the ray hits*/
double	calc_dis(t_vars *data, t_map *map, t_step *step, t_raydir *dir)
{
	if (map->side == 0)
		return ((map->map_x - data->plx + (1 - step->step_x) / 2.0) / dir->x);
	else
		return ((map->map_y - data->ply + (1 - step->step_y) / 2.0) / dir->y);
}

/*Packages all informate about the ray into a t_ray struct*/
t_ray	build_ray(t_vars *data, t_raydir *dir, t_map *map, double dist)
{
	t_ray	ray;

	ray.hit_x = map->map_x;
	ray.hit_y = map->map_y;
	ray.side = map->side;
	ray.distance = dist;
	ray.wall_hit_x = data->plx + dir->x * dist;
	ray.wall_hit_y = data->ply + dir->y * dist;
	ray.line.x1 = (int)(data->plx * 32);
	ray.line.y1 = (int)(data->ply * 32);
	ray.line.x2 = (int)(ray.wall_hit_x * 32);
	ray.line.y2 = (int)(ray.wall_hit_y * 32);
	return (ray);
}
