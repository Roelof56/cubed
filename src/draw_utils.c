/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 12:49:35 by roelof        #+#    #+#                 */
/*   Updated: 2025/07/29 09:39:53 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Function to set a pixel using mlx_put_pixel
void	set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

// convert color struct to int value
int	ft_get_rgba(t_color color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | color.a);
}

// set all pixels data to zero.
void	clear_image(mlx_image_t *img)
{
	uint32_t	i;

	i = 0;
	while (i < img->width * img->height)
	{
		img->pixels[i * 4 + 0] = 0;
		img->pixels[i * 4 + 1] = 0;
		img->pixels[i * 4 + 2] = 0;
		img->pixels[i * 4 + 3] = 0;
		i++;
	}
}

// Fill img -> only used for minimap background .
void	fill_image_color(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

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

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}
