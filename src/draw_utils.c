#include "header.h"

// for mlx_put_pixel
int	ft_get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// set all pixels data to zero.
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

// Function to set a pixel using mlx_put_pixel
void set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
    if (x < img->width && y < img->height)
        mlx_put_pixel(img, x, y, color);
}

// Outline img -> tmp for placement in window
void draw_image_outline(mlx_image_t *img, uint32_t color)
{
	uint32_t x;
	uint32_t y;

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
