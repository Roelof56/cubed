/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_fov.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 10:18:26 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/15 15:45:57 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

// Function to set a pixel using mlx_put_pixel
void set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

// dda to calculate rays 
static t_ray ray_wall(t_vars *data, double angle)
{
    t_ray	ray;
    double	ray_dir_x = cos(angle);
    double	ray_dir_y = sin(angle);

    int		map_x = (int)data->plx;
    int		map_y = (int)data->ply;

    double	delta_dist_x = fabs(1.0 / ray_dir_x);
    double	delta_dist_y = fabs(1.0 / ray_dir_y);
    double	side_dist_x;
	double	side_dist_y;

	int		step_x = 0;
	if (ray_dir_x < 0)
		step_x = -1;
	else
		step_x = 1;
 
	int		step_y = 0;
	if (ray_dir_y < 0)
		step_y = -1;
	else
		step_y = 1;

    if (ray_dir_x < 0)
        side_dist_x = (data->plx - map_x) * delta_dist_x;
    else
        side_dist_x = (map_x + 1.0 - data->plx) * delta_dist_x;

    if (ray_dir_y < 0)
        side_dist_y = (data->ply - map_y) * delta_dist_y;
    else
        side_dist_y = (map_y + 1.0 - data->ply) * delta_dist_y;

    int		hit = 0;
	int		side;
    while (!hit)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        if (data->themap[map_y][map_x] == '1')
            hit = 1;
    }

    // PERPENDICULAR DISTANCE to the wall:
    double	perp_wall_dist;
    if (side == 0)
        perp_wall_dist = (map_x - data->plx + (1 - step_x) / 2.0) / ray_dir_x;
    else
	{
        perp_wall_dist = (map_y - data->ply + (1 - step_y) / 2.0) / ray_dir_y;
	}

	ray.hit_x = map_x;
	ray.hit_y = map_y;
    ray.distance = perp_wall_dist;
    ray.side = side;
    ray.line.x1 = (int)(data->plx * 32);
    ray.line.y1 = (int)(data->ply * 32);
    ray.line.x2 = (int)((data->plx + ray_dir_x * perp_wall_dist) * 32);
    ray.line.y2 = (int)((data->ply + ray_dir_y * perp_wall_dist) * 32);

    return (ray);
}

void	clear_image(mlx_image_t *img)
{
	uint32_t i = 0;
	while (i < img->width * img->height)
	{
		// Each pixel = 4 bytes (RGBA)
		img->pixels[i * 4 + 0] = 0; // R
		img->pixels[i * 4 + 1] = 0; // G
		img->pixels[i * 4 + 2] = 0; // B
		img->pixels[i * 4 + 3] = 0; // A
		i++;
	}
}

double normalize_angle(double angle)
{
    while (angle < 0)
        angle += 2 * PI;
    while (angle >= 2 * PI)
        angle -= 2 * PI;
    return angle;
}

void draw_3d_view(t_vars *data)
{
    int		screen_w   = data->view3d->width;
    int		screen_h   = data->view3d->height;
    double	fov      = PI / 3.0;
    double	start_a  = data->pla - fov / 2.0;
    // double	proj_plane = (screen_w / 2.0) / tan(fov / 2.0);

    clear_image(data->view3d);
	
	int		px = 0;
    while (px < screen_w)
    {
        // map this screen‐column to a ray index in [0,num_rays)
        double	ray_frac = (double)px / (double)screen_w;
        double	angle    = normalize_angle(start_a + ray_frac * fov);
        t_ray	info      = ray_wall(data, angle);

		double raw_dist = info.distance;
		double proj_dist = raw_dist * cos(angle - data->pla);
		if (proj_dist < 0.01)
			proj_dist = 0.01;
			
		double line_height = screen_h / proj_dist;
			
		int draw_start = (int)(-line_height / 2 + screen_h / 2);
		int draw_end   = (int)(line_height / 2 + screen_h / 2);
		
		if (draw_start < 0) 
			draw_start = 0;
		if (draw_end > screen_h)
			draw_end = screen_h;

		/*Choose which texture based on direction*/
		mlx_texture_t *tex;
		if (info.side == 0)
		{
			if (cos(angle) > 0)
				tex = data->textures.ea;
			else
				tex = data->textures.we;
		}
		else
		{
			if (sin(angle) > 0)
				tex = data->textures.so;
			else
				tex = data->textures.no;
		}
		
		/*Compute exact X hit point on wall*/
		double wall_x;
		if (info.side == 0)
			wall_x = data->ply + raw_dist * sin(angle);
		else
			wall_x = data->plx + raw_dist * cos(angle);
		wall_x -= floor(wall_x);
		
		int tex_width = tex->width;
		// int tex_height = tex->height;
		
		int tex_x = (int)(wall_x * tex_width);
		if ((info.side == 0 && cos(angle) > 0) || (info.side == 1 && sin(angle) < 0))
			tex_x = tex_width - tex_x - 1;
		
        uint32_t	ceil_col = ft_get_rgba(data->textures.c);
        uint32_t	floor_col= ft_get_rgba(data->textures.f);

        // draw this single‐px slice
		int		y = 0;
		while (y < draw_start)
		{
			set_pixel(data->view3d, px, y, ceil_col);
			y++;
		}
		
		double step = (double)tex->height / line_height;
		double tex_pos = (draw_start - screen_h / 2 + line_height / 2) * step;

		y = draw_start;
		while (y < draw_end)
		{
			uint32_t tex_y = (int)(tex_pos);
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= tex->height)
				tex_y = tex->height - 1;
			tex_pos += step;
			
			int i = (tex_y * tex->width + tex_x) * 4;
			uint8_t r = tex->pixels[i + 0];
			uint8_t g = tex->pixels[i + 1];
			uint8_t b = tex->pixels[i + 2];
			uint8_t a = tex->pixels[i + 3];
			uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
			
			// Optional: darken horizontal walls slightly
			if (info.side == 1)
			{
				r = (uint8_t)(r * 0.7);
				g = (uint8_t)(g * 0.7);
				b = (uint8_t)(b * 0.7);
				color = (r << 24) | (g << 16) | (b << 8) | a;
			}
			set_pixel(data->view3d, px, y, color);
			y++;
		}

		y = draw_end;
		while (y < screen_h)
		{
			set_pixel(data->view3d, px, y, floor_col);
			y++;
		}
		px++;
    }
}

