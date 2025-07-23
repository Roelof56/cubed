/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 11:59:04 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/23 12:00:39 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

// Function to set a pixel using mlx_put_pixel
void	set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

// Outline img -> tmp for placement in window
void	draw_image_outline(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	while (x < img->width)
	{
		mlx_put_pixel(img, x, 0, color);
		mlx_put_pixel(img, x, img->height - 1, color);
		x++;
	}
	y = 1;
	while (y < img->height - 1)
	{
		mlx_put_pixel(img, 0, y, color);
		mlx_put_pixel(img, img->width - 1, y, color);
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
