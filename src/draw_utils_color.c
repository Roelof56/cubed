#include "header.h"

// convert color struct to int vallue
int	ft_get_rgba(t_color color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | color.a);
}

// Fill img -> tmp, delete later.
void fill_image_color(mlx_image_t *img, uint32_t color)
{
	uint32_t x;
	uint32_t y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			set_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

// Function to draw a line using Bresenham's algorithm
// make norminette approved...
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

