/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_fov.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 10:18:26 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/23 10:31:18 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "ray_caster.h"

static void	init_structs(t_vars *data, t_raydir *dir, t_map *map, double angle)
{
	dir->x = cos(angle);
	dir->y = sin(angle);
	map->x = (int)data->plx;
	map->y = (int)data->ply;
}

static void	init_step_data(t_vars *data, t_raydir *dir, t_map *map, t_step *step)
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

static void	dda(t_vars *data, t_map *map, t_step *step)
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

static double	calculate_distance(t_vars *data, t_map *map, t_step *step, t_raydir *dir)
{
	if (map->side == 0)
		return ((map->x - data->plx + (1 - step->x) / 2.0) / dir->x);
	else
		return ((map->y - data->ply + (1 - step->y) / 2.0) / dir->y);
}

static t_ray	build_ray(t_vars *data, t_raydir *dir, t_map *map, double dist)
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

static t_ray	ray_wall(t_vars *data, double angle)
{
	t_raydir	dir;
	t_map		map;
	t_step		step;
	double		dist;

	init_structs(data, &dir, &map, angle);
	init_step_data(data, &dir, &map, &step);
	dda(data, &map, &step);
	dist = calculate_distance(data, &map, &step, &dir);
	return (build_ray(data, &dir, &map, dist));
}

static t_proj	project(t_ray *info, double angle, int screen_h, t_vars *data)
{
	t_proj	proj;

	proj.raw_dist = info->distance;
	proj.proj_dist = proj.raw_dist * cos(angle - data->pla);
	if (proj.proj_dist < 0.01)
		proj.proj_dist = 0.01;
	proj.line_height = screen_h / proj.proj_dist;
	proj.start = (int)(-proj.line_height / 2 + screen_h / 2);
	proj.end = (int)(proj.line_height / 2 + screen_h / 2);
	if (proj.start < 0)
		proj.start = 0;
	if (proj.end > screen_h)
		proj.end = screen_h;
	return (proj);
}

static mlx_texture_t *get_wall_texture(t_vars *data, int side, double angle)
{
	if (side == 0)
	{
		if (cos(angle > 0))
			return (data->textures.ea);
		else
			return (data->textures.we);
	}
	else
	{
		if (sin(angle) > 0)
			return (data->textures.so);
		else
			return (data->textures.no);
	}
}

static t_texinfo prepare_texture_info(t_tex_input *in)
{
	t_texinfo tinfo;
	double wall_x;
	
	if (in->info->side == 0)
		wall_x = in->data->ply + in->proj->raw_dist * sin(in->angle);
	else
		wall_x = in->data->plx + in->proj->raw_dist * cos(in->angle);
	wall_x -= floor(wall_x);
	tinfo.tex = in->tex;
	tinfo.tex_x = (int)(wall_x * in->tex->width);
	if ((in->info->side == 0 && cos(in->angle) > 0) ||
		(in->info->side == 1 && sin(in->angle) < 0))
		tinfo.tex_x = in->tex->width - tinfo.tex_x - 1;
	tinfo.step = (double)in->tex->height / in->proj->line_height;
	tinfo.pos = (in->proj->start - (int)(in->data->view3d->height / 2)
				+ (in->proj->line_height / 2)) * tinfo.step;
	return (tinfo);
}

static void	draw_ceiling_and_floor(t_vars *data, int px, t_proj *proj)
{
	int			y;
	uint32_t	ceil_color;
	uint32_t	floor_col;

	y = 0;
	ceil_color = ft_get_rgba(data->textures.c);
	while (y < proj->start)
		set_pixel(data->view3d, px, y++, ceil_color);
	y = proj->end;
	floor_col = 0;
	while (y < (int)data->view3d->height)
		set_pixel(data->view3d, px, y++, floor_col);
}

static void	draw_wall(t_vars*data, int px, t_render_data *r)
{
	int			y;
	int			tex_y;
	int			i;
	uint8_t		r_val;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	uint32_t	color;

	y = r->proj->start;
	while (y < r->proj->end)
	{
		tex_y = (int)(r->tinfo->pos);
		r->tinfo->pos += r->tinfo->step;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)r->tinfo->tex->height)
			tex_y = r->tinfo->tex->height - 1;
		i = (tex_y * r->tinfo->tex->width + r->tinfo->tex_x) * 4;
		r_val = r->tinfo->tex->pixels[i];
		g = r->tinfo->tex->pixels[i + 1];
		b = r->tinfo->tex->pixels[i + 2];
		a = r->tinfo->tex->pixels[i + 3];
		if (r->info->side == 1)
		{
			r_val *= 0.7;
			g *= 0.7;
			b *= 0.7;
		}
		color = (r_val << 24) | (g << 16) | (b << 8) | a;
		set_pixel(data->view3d, px, y++, color);
	}
}

static void	draw_slice(t_vars *data, int px, t_render_data *r)
{
	draw_ceiling_and_floor(data, px, r->proj);
	draw_wall(data, px, r);
}

void draw_3d_view(t_vars *data)
{
	int				screen_w;
	int				screen_h;
	double			fov;
	double			start_a;
	int				px;
	t_ray			info;
	t_proj			proj;
	t_tex_input		tin;
	mlx_texture_t	*tex;
	t_texinfo		tinfo;
	t_render_data	rdata;

	screen_w = data->view3d->width;
	screen_h = data->view3d->height;
	fov = PI / 3.0;
	start_a = data->pla - fov / 2.0;
	clear_image(data->view3d);
	px = 0;
	while (px < screen_w)
	{
		double ray_frac = (double)px / (double)screen_w;
		double angle = normalize_angle(start_a + ray_frac * fov);
		info = ray_wall(data, angle);
		proj = project(&info, angle, screen_h, data);
		tex = get_wall_texture(data, info.side, angle);
		tin.info = &info;
		tin.angle = angle;
		tin.proj = &proj;
		tin.data = data;
		tin.tex = tex;
		tinfo = prepare_texture_info(&tin);
		rdata.proj = &proj;
		rdata.tinfo = &tinfo;
		rdata.info = &info;
		draw_slice(data, px, &rdata);
		px++;
	}
}



