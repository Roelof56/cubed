/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_fov.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 10:18:26 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/08 15:21:57 by jilustre      ########   odam.nl         */
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
        perp_wall_dist = (map_y - data->ply + (1 - step_y) / 2.0) / ray_dir_y;

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

// Function to draw a line using Bresenham's algorithm
// move to draw_utils.c
void bresenham_line(mlx_image_t *img, t_line line, uint32_t color)
{
	int dx = abs(line.x2 - line.x1);
	int dy = abs(line.y2 - line.y1);

	int sx; // new;
	int sy;

	int e2;
	int err;

	//direction.
	if (line.x1 < line.x2)
		sx = 1;
	else
		sx = -1;

	if (line.y1 < line.y2)
		sy = 1;
	else
		sy = -1;

	err = dx - dy;
	while (1) {
		set_pixel(img, line.x1, line.y1, color);
		if (line.x1 == line.x2 && line.y1 == line.y2) // Reached endpoint
			break;

		e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			line.x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			line.y1 += sy;
		}
	}
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

// original fov for non zoomed minimap
void draw_fov_line(t_vars *data)
{
	const int num_rays = 60;
	const double fov = PI / 3;
	const double start_angle = data->pla - fov / 2;
	const double step = fov / num_rays;

	clear_image(data->fovlines);

	for (int i = 0; i <= num_rays; i++)
	{
		double angle = start_angle + i * step;
		t_ray ray = ray_wall(data, angle);
		bresenham_line(data->fovlines, ray.line, 0xFFFFFF);
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
    double	proj_plane = (screen_w / 2.0) / tan(fov / 2.0);

    clear_image(data->view3d);
	
	int		px = 0;
    while (px < screen_w)
    {
        // map this screen‐column to a ray index in [0,num_rays)
        double	ray_frac = (double)px / (double)screen_w;
        double	angle    = normalize_angle(start_a + ray_frac * fov);
        t_ray	info      = ray_wall(data, angle);

        double	dist = info.distance * cos(angle - data->pla); // multiplying it with cos solves fisheye effect
        if (dist < 0.01)
			dist = 0.01;

        int		wall_h = (int)((1.0 * proj_plane) / dist);
        if (wall_h > screen_h)
			wall_h = screen_h;

        int		top = (screen_h / 2) - (wall_h / 2);
        int		bottom = top + wall_h;
        if (top < 0)
			top = 0;
        if (bottom > screen_h)
			bottom = screen_h;

        uint32_t	ceil_col = 0xFF00FF;
		uint32_t	wall_col;
		if (info.side)
			wall_col = 0x888888;
		else
			wall_col = 0xAAAAAA;
        uint32_t	floor_col= 0x00FFFF;

        // draw this single‐px slice
		int		y = 0;
		while (y < top)
		{
			set_pixel(data->view3d, px, y, ceil_col);
			y++;
		}
		y = top;
		while (y < bottom)
		{
			set_pixel(data->view3d, px, y, wall_col);
			y++;
		}
		y = bottom;
		while (y < screen_h)
		{
			set_pixel(data->view3d, px, y, floor_col);
			y++;
		}
		px++;
    }
}
