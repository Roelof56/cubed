/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/24 10:35:06 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/29 09:52:39 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "ray_caster.h"

/*Converts wall hit distance into an on screen vertical height*/
t_proj	project(t_ray *info, double angle, int screen_h, t_vars *data)
{
	t_proj	proj;

	proj.raw_dist = info->distance;
	proj.proj_dist = proj.raw_dist * cos(angle - data->pla);
	if (proj.proj_dist < 0.01)
		proj.proj_dist = 0.01;
	proj.line_height = screen_h / proj.proj_dist;
	proj.pixel_start = (int)(-proj.line_height / 2 + screen_h / 2);
	proj.pixel_end = (int)(proj.line_height / 2 + screen_h / 2);
	if (proj.pixel_start < 0)
		proj.pixel_start = 0;
	if (proj.pixel_end > screen_h)
		proj.pixel_end = screen_h;
	return (proj);
}

/*Picks the correct texture based on which side of wall was hit*/
mlx_texture_t	*get_wall_texture(t_vars *data, int side, double angle)
{
	if (side == 0)
	{
		if (cos(angle) > 0)
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

/*Computes which part of the texture to draw based on the ray hits the wall*/
t_tex_info	prepare_texture_info(t_tex_input *in)
{
	t_tex_info	tinfo;
	double		wall_x;

	if (in->ray_info->side == 0)
		wall_x = in->data->ply + in->proj->raw_dist * sin(in->angle);
	else
		wall_x = in->data->plx + in->proj->raw_dist * cos(in->angle);
	wall_x -= floor(wall_x);
	tinfo.tex = in->tex;
	tinfo.tex_x = (int)(wall_x * in->tex->width);
	if ((in->ray_info->side == 0 && cos(in->angle) > 0)
		|| (in->ray_info->side == 1 && sin(in->angle) < 0))
		tinfo.tex_x = in->tex->width - tinfo.tex_x - 1;
	tinfo.step = (double)in->tex->height / in->proj->line_height;
	tinfo.pos = (in->proj->pixel_start - (int)(in->data->view3d->height / 2)
			+ (in->proj->line_height / 2)) * tinfo.step;
	return (tinfo);
}

/*Fills pixels above and below the wall with colors from map file*/
void	draw_ceiling_and_floor(t_vars *data, int px, t_proj *proj)
{
	int			y;
	uint32_t	ceil_color;
	uint32_t	floor_col;

	y = 0;
	ceil_color = ft_get_rgba(data->textures.c);
	while (y < proj->pixel_start)
		set_pixel(data->view3d, px, y++, ceil_color);
	y = proj->pixel_end;
	floor_col = ft_get_rgba(data->textures.f);
	while (y < (int)data->view3d->height)
		set_pixel(data->view3d, px, y++, floor_col);
}

/*Samples one pixel from the wall texture at current tex position*/
uint32_t	pixel_texture(t_tex_info *tinfo, t_ray *info)
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
