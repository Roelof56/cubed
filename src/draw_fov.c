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
static void set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x > 0 && y > 0) //& within minimap bounds ?
	{
		if (x < 700 && y < 700)
			mlx_put_pixel(img, x, y, color);
	}
}

/* round off double to int */// -> just use math.h
// static int double_to_int(double nbr)
// {
// 	int res;

// 	if (nbr >= 0)
// 		res = (int)(nbr + 0.5);
// 	else
// 		res = (int)(nbr - 0.5);

// 	return res;
// }

/* set line struct - startpoint & endpoint. */
static t_line get_line_endpoints(t_vars *data)
{
	t_line	line;

	// Set starting point at the center
	// line.x1 = (int)data->plx;
	// line.y1 = (int)data->ply;.
	line.x1 = (int)round(data->plx);
	line.y1 = (int)round(data->ply);

	// Extend line in delta x y dir.
	line.x2 = line.x1 + (int)(data->pdx * 1);
	line.y2 = line.y1 + (int)(data->pdy * 1);

	return (line);
}

// Function to draw a line using Bresenham's algorithm
void bresenham_line(mlx_image_t *img, t_line line, uint32_t color) {
	int dx = abs(line.x2 - line.x1);
	int dy = abs(line.y2 - line.y1);

	int sx; // new;
	int sy;

	int e2;
	int err;

	// int sx = (line.x1 < line.x2) ? 1 : -1;
	// int sy = (line.y1 < line.y2) ? 1 : -1; //illegal ternary

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

static void	test_scale_line(t_line *line)
{
	line->x1 = line->x1 * 32;
	line->y1 = line->y1 * 32;
	line->x2 = line->x2 * 32;
	line->y2 = line->y2 * 32;
}

void	draw_fov_line(t_vars *data)
{
	t_line line;

	mlx_delete_image(data->mlx, data->fovlines);
	
	data->fovlines = mlx_new_image(data->mlx, 700, 400);
	line = get_line_endpoints(data);

	test_scale_line(&line);
	
	bresenham_line(data->fovlines, line, 0xFFFFFF);
	// printf("test2\n");
	mlx_image_to_window(data->mlx, data->fovlines, 0, 0);
}
