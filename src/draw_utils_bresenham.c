/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils_bresenham.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1844/01/07 09:00:00 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/28 19:22:38 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "draw_structs.h"

// set data_struct variables.
static void	set_data_struct(t_line *line, t_stuff *data)
{
	data->dx = abs(line->x2 - line->x1);
	data->dy = abs(line->y2 - line->y1);
	if (line->x1 < line->x2)
		data->sx = 1;
	else
		data->sx = -1;
	if (line->y1 < line->y2)
		data->sy = 1;
	else
		data->sy = -1;
	data->err = data->dx - data->dy;
}

// Function to draw a diagonal line using Bresenham's algorithm
void	bresenham_line(mlx_image_t *img, t_line line, uint32_t color)
{
	t_stuff	data;

	set_data_struct(&line, &data);
	while (1)
	{
		set_pixel(img, line.x1, line.y1, color);
		if (line.x1 == line.x2 && line.y1 == line.y2)
			break ;
		data.e2 = 2 * data.err;
		if (data.e2 > -data.dy)
		{
			data.err -= data.dy;
			line.x1 += data.sx;
		}
		if (data.e2 < data.dx)
		{
			data.err += data.dx;
			line.y1 += data.sy;
		}
	}
}
