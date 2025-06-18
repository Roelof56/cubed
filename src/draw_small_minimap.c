#include "header.h"

// void compute_map_dimensions(t_vars *data)
// {
// 	int i = 0;
// 	int max_width = 0;
// 	while (data->themap[i])
// 	{
// 		int len = ft_strlen(data->themap[i]);
// 		if (len > max_width)
// 			max_width = len;
// 		i++;
// 	}
// 	data->mapheight = i;
// 	data->mapwidth = max_width;
// }

// draw a 4x4 square (orange)
static void	draw_player(mlx_image_t *img, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(img, ((x - 2) + j), ((y - 2) + i), 0xFFA500FF); // this is not mid of minimap...
			j++;
		}
		i++;
	}
}

// Outline an image
static void draw_image_outline(mlx_image_t *img, uint32_t color)
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

// draw wall block - red
// static void draw_block(mlx_image_t *img, float x, float y, uint32_t color)
// {
// 	int i;
// 	int	newx;
// 	int	newy;

// 	newx = (int)round(x * MMSCALE);
// 	newy = (int)round(y * MMSCALE);
// 	// printf("newx: %d\n", newx);
// 	i = 0;
// 	while (i < MMSCALE)
// 	{
// 		mlx_put_pixel(img, (newx + i), newy, color);
// 		mlx_put_pixel(img, (newx + i), (newy + MMSCALE), color);
// 		i++;
// 	}
// 	i = 1;
// 	while (i < MMSCALE)
// 	{
// 		mlx_put_pixel(img, newx, (newy + i), color);
// 		mlx_put_pixel(img, (newx + MMSCALE), (newy + i), color);
// 		i++;
// 	}
// }

// // draw floor block - grey.
// static void draw_floor(mlx_image_t *img, float x, float y, uint32_t color)
// {
// 	int i;
// 	int	newx;
// 	int	newy;

// 	newx = (int)round(x * MMSCALE) + 1;
// 	newy = (int)round(y * MMSCALE) + 1;
// 	// printf("newx: %d\n", newx);
// 	i = 0;
// 	while (i < MMSCALE - 1)
// 	{
// 		mlx_put_pixel(img, (newx + i), newy, color);
// 		mlx_put_pixel(img, (newx + i), (newy + MMSCALE), color);
// 		i++;
// 	}
// 	i = 1;
// 	while (i < MMSCALE - 1)
// 	{
// 		mlx_put_pixel(img, newx, (newy + i), color);
// 		mlx_put_pixel(img, (newx + MMSCALE), (newy + i), color);
// 		i++;
// 	}
// }



// first attempt thing.
// void	draw_small_minimap(t_vars *data)
// {
// 	draw_image_outline(data->layer1, 0xFFD700FF); //tmp for placement
// 	int i = 0;
// 	int j = 0;
// 	int startx;
// 	int starty;

// 	startx = data->plx -5;
// 	starty = data->ply -5;
// 	while (startx < 0)
// 		startx++;
// 	while (starty < 0)
// 		starty++;
// 	clear_image(data->layer1);
// 	while (j < 10)
// 	{
// 		while (i < 10)
// 		{
// 			if (data->themap[starty + j][startx + i])
// 			{
// 				if (data->themap[starty + j][startx + i] == '1')
// 				{
// 					draw_block(data->layer1, startx + i, starty + j, 0xFF0000FF); //red
// 				}
// 				else
// 					draw_floor(data->layer1, startx + i, starty + j, 0xF5F5DC09); //greyish
// 			}
// 			else
// 				break ;
// 			i++;
// 		}
// 		i = 0;
// 		j++;
// 	}
// 	draw_player(data->layer1, round(data->plx * MMSCALE), round(data->ply * MMSCALE));
// }

void draw_small_minimap(t_vars *data)
{
	int view_w = 10;
	int view_h = 10;
	int startx;
	int starty;

	// compute_map_dimensions(data);

	// Clamp the viewport so it doesn't go outside the map
	startx = (int)(data->plx) - view_w / 2;
	starty = (int)(data->ply) - view_h / 2;
	if (startx < 0)
		startx = 0;
	if (starty < 0)
		starty = 0;
	if (startx + view_w > data->mapwidth)
		startx = data->mapwidth - view_w;
	if (starty + view_h > data->mapheight)
		starty = data->mapheight - view_h;

	clear_image(data->layer1);
	draw_image_outline(data->layer1, 0xFFD700FF); // optional border

	// int j = 0;
	// while (j < view_h)
	// {
	// 	int i = 0;
	// 	while (i < view_w)
	// 	{
	// 		char tile = data->themap[starty + j][startx + i];
	// 		if (tile)
	// 		{
	// 			if (tile == '1')
	// 				draw_block(data->layer1, i, j, 0xFF0000FF); // red
	// 			else
	// 				draw_floor(data->layer1, i, j, 0xF5F5DC09); // beige-ish
	// 		}
	// 		i++;
	// 	}
	// 	j++;
	// }

	// Draw player relative to startx/starty
	float px = (data->plx - startx) * MMSCALE;
	float py = (data->ply - starty) * MMSCALE;
	draw_player(data->layer1, round(px), round(py));
}
