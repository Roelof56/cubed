#include "cubed.h"

// M_PI is defined in <math.h>
// take agle in degree -> return radians
double degree_to_radians(double degree)
{
	double	pi;
	double	retval;
	
	pi = M_PI; 
	retval = degree * pi / 180.0;
	return (retval);
}

// Function to set a pixel using mlx_put_pixel
void set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < TWIDTH && y < THEIGHT)
		mlx_put_pixel(img, x, y, color);
}

// old one _ thru middle
t_line	calculate_line_endpoints(double angle) {
	int		center_x;
	int		center_y;
	double	radians;
	double	dx;
	double	dy;
	t_line	line;

	center_x = TWIDTH / 2;
	center_y = THEIGHT / 2;
	radians = degree_to_radians(angle);
	dx = cos(radians);
	dy = sin(radians);
	line.x1 = center_x - (int)(dx * TWIDTH);
	line.y1 = center_y - (int)(dy * THEIGHT);
	line.x2 = center_x + (int)(dx * TWIDTH);
	line.y2 = center_y + (int)(dy * THEIGHT);
	return (line);
}

/* from center. */
t_line calculate_line_direction(double angle) {
	int		center_x;
	int		center_y;
	double	radians;
	double	dx;
	double	dy;
	t_line	line;

	center_x = TWIDTH / 2;
	center_y = THEIGHT / 2;
	radians = degree_to_radians(angle);

	// Calculate direction vector
	dx = cos(radians);
	dy = sin(radians);

	// Set starting point at the center
	line.x1 = center_x;
	line.y1 = center_y;

	// Extend the line to the edge of the image in the given direction
	line.x2 = center_x + (int)(dx * (TWIDTH / 2));
	line.y2 = center_y + (int)(dy * (THEIGHT / 2));

	return (line);
}

// Function to draw a line using Bresenham's algorithm
void bresenham_line(mlx_image_t *img, t_line line, uint32_t color) {
	int dx = abs(line.x2 - line.x1);
	int dy = abs(line.y2 - line.y1);
	int sx = (line.x1 < line.x2) ? 1 : -1;
	int sy = (line.y1 < line.y2) ? 1 : -1; //illegal ternary
	
	int e2;
	int err;

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
	// commented out cause unused.
// void draw_line_bresenham(mlx_image_t *img, double angle)
// {
// 	t_line	line;
// 	line = calculate_line_endpoints(angle);
// 	bresenham_line(img, line, 0xFFFFFF);
// }

//from center.
void draw_line_in_direction(mlx_image_t *img, double angle) {
	t_line line;
	line = calculate_line_direction(angle);
	bresenham_line(img, line, 0xFFFFFF);
}

void	draw_minimap_player(t_vars *vars)
{
	mlx_delete_image(vars->mlx, vars->td_player);
	vars->td_player = mlx_texture_to_image(vars->mlx, vars->tdpl);
	draw_line_in_direction(vars->td_player, vars->pl_angle);

	mlx_image_to_window(vars->mlx, vars->td_player, (vars->pl_x * 32), (vars->pl_y * 32));
}
