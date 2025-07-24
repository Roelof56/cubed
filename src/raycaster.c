/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/24 09:58:15 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/24 10:23:59 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "ray_caster.h"

t_ray	ray_wall(t_vars *data, double angle)
{
	t_raydir	dir;
	t_map		map;
	t_step		step;
	double		dist;

	init_structs(data, &dir, &map, angle);
	init_step(data, &dir, &map, &step);
	dda(data, &map, &step);
	dist = calc_dist(data, &map, &step, &dir);
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

static mlx_texture_t	*get_wall_texture(t_vars *data, int side, double angle)
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

static t_texinfo	prepare_texture_info(t_tex_input *in)
{
	t_texinfo	tinfo;
	double		wall_x;

	if (in->info->side == 0)
		wall_x = in->data->ply + in->proj->raw_dist * sin(in->angle);
	else
		wall_x = in->data->plx + in->proj->raw_dist * cos(in->angle);
	wall_x -= floor(wall_x);
	tinfo.tex = in->tex;
	tinfo.tex_x = (int)(wall_x * in->tex->width);
	if ((in->info->side == 0 && cos(in->angle) > 0)
		|| (in->info->side == 1 && sin(in->angle) < 0))
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

uint32_t	pixel_texture(t_texinfo *tinfo, t_ray *info)
{
	int		tex_y;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	tex_y = (int)(tinfo->pos);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)tinfo->tex->height)
		tex_y = tinfo->tex->height - 1;
	r = tinfo->tex->pixels[(tex_y * tinfo->tex->width + tinfo->tex_x) * 4];
	g = tinfo->tex->pixels[(tex_y * tinfo->tex->width + tinfo->tex_x) * 4 + 1];
	b = tinfo->tex->pixels[(tex_y * tinfo->tex->width + tinfo->tex_x) * 4 + 2];
	a = tinfo->tex->pixels[(tex_y * tinfo->tex->width + tinfo->tex_x) * 4 + 3];
	if (info->side == 1)
	{
		r *= 0.7;
		g *= 0.7;
		b *= 0.7;
	}
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

static void	draw_wall(t_vars *data, int px, t_render_data *r)
{
	int			y;
	uint32_t	color;

	y = r->proj->start;
	while (y < r->proj->end)
	{
		color = pixel_texture(r->tinfo, r->info);
		set_pixel(data->view3d, px, y++, color);
		r->tinfo->pos += r->tinfo->step;
	}
}

static void	draw_slice(t_vars *data, int px, t_render_data *r)
{
	draw_ceiling_and_floor(data, px, r->proj);
	draw_wall(data, px, r);
}

void	render_column(t_vars *data, t_render_state *s)
{
	double			ray_frac;
	double			angle;
	mlx_texture_t	*tex;
	t_tex_input		tin;

	ray_frac = (double)s->px / (double)s->screen_w;
	angle = normalize_angle(s->start_a + ray_frac * s->fov);
	s->info = ray_wall(data, angle);
	s->proj = project(&s->info, angle, s->screen_h, data);
	tex = get_wall_texture(data, s->info.side, angle);
	tin.info = &s->info;
	tin.angle = angle;
	tin.proj = &s->proj;
	tin.data = data;
	tin.tex = tex;
	s->tinfo = prepare_texture_info(&tin);
	s->rdata.proj = &s->proj;
	s->rdata.tinfo = &s->tinfo;
	s->rdata.info = &s->info;
	draw_slice(data, s->px, &s->rdata);
}

void	draw_3d_view(t_vars *data)
{
	t_render_state	s;

	s.screen_w = data->view3d->width;
	s.screen_h = data->view3d->height;
	s.fov = PI / 3.0;
	s.start_a = data->pla - s.fov / 2.0;
	clear_image(data->view3d);
	s.px = 0;
	while (s.px < s.screen_w)
	{
		render_column(data, &s);
		s.px++;
	}
}
