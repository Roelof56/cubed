#include "header.h"

// Function to draw a line using Bresenham's algorithm
static void bresenham_line(mlx_image_t *img, t_line line, uint32_t color)
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

static t_line ray_wall(t_vars *data, double angle)
{
	t_line	line;

	double	ray_x = data->plx; // is this the problem ?	
	double	ray_y = data->ply;

	double	dx = cos(angle);
	double	dy = sin(angle);
	double	step = 0.05; // fine enough step for smooth lines
	int		map_x; 
	int		map_y;

	// line.x1 = (int)(data->plx * 16); 
	// line.y1 = (int)(data->ply * 16);
	line.x1 = data->layer1->width / 2;
	line.y1 = data->layer1->height / 2; // change to center of img.

	while (1)
	{
		ray_x += dx * step;
		ray_y += dy * step;
		map_x = (int)(ray_x);
		map_y = (int)(ray_y);
		if (data->themap[map_y][map_x] == '1') // hit wall
			break;
	}
	line.x2 = (int)(ray_x * 16);
	line.y2 = (int)(ray_y * 16);
	return (line);
}

// for small minimap.
void	new_draw_fov_line(t_vars *data)
{
	const int num_rays = 30;  // number of rays
	const double fov = PI / 3;  // 60 degrees field of view
	const double start_angle = data->pla - fov / 2;
	const double step = fov / num_rays;
	int	i = 0;
	t_line line;

	while (i < num_rays)
	{
		double angle = start_angle + i * step;
		line = ray_wall(data, angle);
		bresenham_line(data->layer1, line, 0xFFFFFF);
		i++;
	}
}
