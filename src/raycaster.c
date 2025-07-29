/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/24 09:58:15 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/29 09:53:52 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "ray_caster.h"

/*Wrapper that casts a single ray at the given angle and returns t_ray*/
t_ray	ray_wall(t_vars *data, double angle)
{
	t_raydir	dir;
	t_map		map;
	t_step		step;
	double		dist;

	init_ray(data, &dir, &map, angle);
	ini_step(data, &dir, &map, &step);
	dda(data, &map, &step);
	dist = calc_dis(data, &map, &step, &dir);
	return (build_ray(data, &dir, &map, dist));
}

/*Draws the textured vertical slice of the wall*/
static void	draw_wall(t_vars *data, int px, t_render_data *r)
{
	int			y;
	uint32_t	color;

	y = r->proj->pixel_start;
	while (y < r->proj->pixel_end)
	{
		color = pixel_texture(r->tex_map, r->ray);
		set_pixel(data->view3d, px, y++, color);
		r->tex_map->pos += r->tex_map->step;
	}
}

/*Draws one full vertical column*/
static void	draw_slice(t_vars *data, int px, t_render_data *r)
{
	draw_ceiling_and_floor(data, px, r->proj);
	draw_wall(data, px, r);
}

/*Does everything for one vertical screen column*/
static void	render_column(t_vars *data, t_render_state *s)
{
	double			ray_frac;
	double			angle;
	mlx_texture_t	*tex;
	t_tex_input		tin;

	ray_frac = (double)s->px / (double)s->screen_w;
	angle = normalize_angle(s->start_angle + ray_frac * s->fov);
	s->ray = ray_wall(data, angle);
	s->proj = project(&s->ray, angle, s->screen_h, data);
	tex = get_wall_texture(data, s->ray.side, angle);
	tin.ray_info = &s->ray;
	tin.angle = angle;
	tin.proj = &s->proj;
	tin.data = data;
	tin.tex = tex;
	s->tex_map = prepare_texture_info(&tin);
	s->column.proj = &s->proj;
	s->column.tex_map = &s->tex_map;
	s->column.ray = &s->ray;
	draw_slice(data, s->px, &s->column);
}

/*Main loop to render the entire 3D screen*/
void	draw_3d_view(t_vars *data)
{
	t_render_state	s;

	s.screen_w = data->view3d->width;
	s.screen_h = data->view3d->height;
	s.fov = PI / 3.0;
	s.start_angle = data->pla - s.fov / 2.0;
	clear_image(data->view3d);
	s.px = 0;
	while (s.px < s.screen_w)
	{
		render_column(data, &s);
		s.px++;
	}
}
