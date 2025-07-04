#include "header.h"

// M_PI is defined in <math.h> but squigly line made me define my own.
// take agle in degree -> return radians
// double degree_to_radians(double degree)
// {
// 	double	pi;
// 	double	retval;
	
// 	pi = PI; 
// 	retval = degree * pi / 180.0;
// 	return (retval);
// }

// Function to set a pixel using mlx_put_pixel
void set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x > 0 && y > 0) //& within minimap bounds ?
	{
		if (x < 700 && y < 700)
			mlx_put_pixel(img, x, y, color);
	}
}

// calculate line points in map
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

	// line.x1 = (int)(data->plx * 32);
	// line.y1 = (int)(data->ply * 32);
	line.x1 = (int)data->plx;
	line.y1 = (int)data->ply;

	while (1)
	{
		ray_x += dx * step;
		ray_y += dy * step;
		map_x = (int)(ray_x);
		map_y = (int)(ray_y);
		if (data->themap[map_y][map_x] == '1') // hit wall
			break;
	}
	// line.x2 = (int)(ray_x * 32);
	// line.y2 = (int)(ray_y * 32);
	line.x2 = (int)ray_x;
	line.y2 = (int)ray_y;
	return (line);
}

// Get the length of a line in pixels
static double	get_line_length(t_line *line)
{
	double	dx;
	double	dy;
	double	result;

	dx = (double)(line->x2 - line->x1);
	dy = (double)(line->y2 - line->y1);
	result = sqrt(dx * dx + dy * dy);
	return (result);
}

// used for calculating line len
void	draw_fov_line(t_vars *data)
{
	const int num_rays = 60;  // number of rays
	const double fov = PI / 3;  // 60 degrees field of view
	const double start_angle = data->pla - fov / 2;
	const double step = fov / num_rays;
	int	i = 0;
	t_line line;

	// clear_image(data->fovlines);
	while (i < num_rays)
	{
		double angle = start_angle + i * step;
		line = ray_wall(data, angle);
		// bresenham_line(data->fovlines, line, 0xFFFFFF);
		double tmp =  get_line_length(&line);
		// printf("%d: linelen: %f\n", i, get_line_length(&line));
		data->array[i] = tmp;
		i++;
	}
}
