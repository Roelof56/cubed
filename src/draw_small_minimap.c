#include "header.h"

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
			mlx_put_pixel(img, ((x - 2) + j), ((y - 2) + i), 0xFFA500FF);
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
static void draw_block(mlx_image_t *img, float x, float y, uint32_t color)
{
	int i;
	int	newx;
	int	newy;

	newx = (int)round(x * MMSCALE);
	newy = (int)round(y * MMSCALE);
	// printf("newx: %d\n", newx);
	i = 0;
	while (i < MMSCALE)
	{
		mlx_put_pixel(img, (newx + i), newy, color);
		mlx_put_pixel(img, (newx + i), (newy + MMSCALE), color);
		i++;
	}
	i = 1;
	while (i < MMSCALE)
	{
		mlx_put_pixel(img, newx, (newy + i), color);
		mlx_put_pixel(img, (newx + MMSCALE), (newy + i), color);
		i++;
	}
}

// draw floor block - grey.
static void draw_floor(mlx_image_t *img, float x, float y, uint32_t color)
{
	int i;
	int	newx;
	int	newy;

	newx = (int)round(x * MMSCALE) + 1;
	newy = (int)round(y * MMSCALE) + 1;
	// printf("newx: %d\n", newx);
	i = 0;
	while (i < MMSCALE - 1)
	{
		mlx_put_pixel(img, (newx + i), newy, color);
		mlx_put_pixel(img, (newx + i), (newy + MMSCALE), color);
		i++;
	}
	i = 1;
	while (i < MMSCALE - 1)
	{
		mlx_put_pixel(img, newx, (newy + i), color);
		mlx_put_pixel(img, (newx + MMSCALE), (newy + i), color);
		i++;
	}
}

	// offset inspiration by ai. I dont like it.
// void draw_small_minimap(t_vars *data)
// {
// 	float view_w = 10;
// 	float view_h = 10;
// 	float startx = data->plx - (view_w / 2.0f);
// 	float starty = data->ply - (view_h / 2.0f);

// 	// Clamp to map bounds
// 	if (startx < 0)
// 		startx = 0;
// 	if (starty < 0)
// 		starty = 0;
// 	if (startx + view_w > data->mapwidth)
// 		startx = data->mapwidth - view_w;
// 	if (starty + view_h > data->mapheight)
// 		starty = data->mapheight - view_h;
// 	if (startx < 0)
// 		startx = 0;
// 	if (starty < 0)
// 		starty = 0;

// 	clear_image(data->layer1);
// 	draw_image_outline(data->layer1, 0xFFD700FF); // border

// 	// For sub-tile pixel shift
// 	float offsetx = startx - floorf(startx);
// 	float offsety = starty - floorf(starty);

// 	int y = 0;
// 	while (y < view_h)
// 	{
// 		int x = 0;
// 		while (x < view_w)
// 		{
// 			int mx = (int)(floorf(startx) + x);
// 			int my = (int)(floorf(starty) + y);

// 			if (my >= data->mapheight || !data->themap[my])
// 			{
// 				x++;
// 				continue;
// 			}
// 			if (mx >= (int)ft_strlen(data->themap[my]))
// 			{
// 				x++;
// 				continue;
// 			}

// 			char tile = data->themap[my][mx];
// 			if (tile == '1')
// 				draw_block(data->layer1, x - offsetx, y - offsety, 0xFF0000FF);
// 			else
// 				draw_floor(data->layer1, x - offsetx, y - offsety, 0xF5F5DC09);

// 			x++;
// 		}
// 		y++;
// 	}

// 	// Draw player relative to sub-tile offset
// 	float px = (data->plx - startx) * MMSCALE;
// 	float py = (data->ply - starty) * MMSCALE;
// 	draw_player(data->layer1, (int)roundf(px), (int)roundf(py));
// }


// try to draw minimap arround player.
void draw_small_minimap(t_vars *data)
{
	float view_w = 10;
	float view_h = 10;
	float startx;
	float starty;
	float px;
	float py;

	// Clamp the viewport so it doesn't go outside the map
	startx = data->plx - (view_w / 2);
	starty = data->ply - (view_h / 2);

	// Clean co-ordinates.
	if (startx < 0)
		startx = 0;
	if (starty < 0)
		starty = 0;
	if (startx + view_w > data->mapwidth)
		startx = data->mapwidth - view_w;
	if (starty + view_h > data->mapheight)
		starty = data->mapheight - view_h;

	clear_image(data->layer1);
	draw_image_outline(data->layer1, 0xFFD700FF); // temp border

	// looptieloop to 
	int y;
	int x;
	y = 0;
	while (y < view_h)
	{
		x = 0;
		while (x < view_w)
		{
			char tile = data->themap[(int)round(starty + y)][(int)round(startx + x)];
			if (tile)
			{
				if (tile == '1')
					draw_block(data->layer1, x , y, 0xFF0000FF); // red // also add offset here ?
				else
					draw_floor(data->layer1, x, y, 0xF5F5DC09); // beige-ish
			}
			x++;
		}
		y++;
	}

	// Draw player relative to startx/starty
	px = (data->plx - startx) * MMSCALE;
	py = (data->ply - starty) * MMSCALE;
	draw_player(data->layer1, (int)roundf(px), (int)roundf(py));
}
