/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_fov.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 10:18:26 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/12 15:18:52 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Function to set a pixel using mlx_put_pixel
static void set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x > 0 && y > 0) //& within minimap bounds ?
	{
		if (x < 700 && y < 700)
			mlx_put_pixel(img, x, y, color);
	}
}

static t_line ray_wall(t_vars *data, double angle)
{
	t_line	line;
	double	ray_x = data->plx;
	double	ray_y = data->ply;
	double	dx = cos(angle);
	double	dy = sin(angle);
	double	step = 0.05; // fine enough step for smooth lines
	int		map_x; 
	int		map_y;

	line.x1 = (int)(data->plx * 32);
	line.y1 = (int)(data->ply * 32);

	while (1)
	{
		ray_x += dx * step;
		ray_y += dy * step;
		map_x = (int)(ray_x);
		map_y = (int)(ray_y);
		if (data->themap[map_y][map_x] == '1') // hit wall
			break;
	}
	line.x2 = (int)(ray_x * 32);
	line.y2 = (int)(ray_y * 32);
	return (line);
}

// Function to draw a line using Bresenham's algorithm
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

void	draw_fov_line(t_vars *data)
{
	const int num_rays = 30;  // number of rays
	const double fov = PI / 3;  // 60 degrees field of view
	const double start_angle = data->pla - fov / 2;
	const double step = fov / num_rays;
	int	i = 0;
	t_line line;

	// mlx_delete_image(data->mlx, data->fovlines);
	// data->fovlines = mlx_new_image(data->mlx, 700, 400);
	clear_image(data->fovlines);
	while (i < num_rays)
	{
		double angle = start_angle + i * step;
		line = ray_wall(data, angle);
		bresenham_line(data->fovlines, line, 0xFFFFFF);
		i++;
	}
	// mlx_image_to_window(data->mlx, data->fovlines, 0, 0);
}
