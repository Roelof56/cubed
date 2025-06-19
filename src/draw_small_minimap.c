#include "header.h"

// Outline img -> tmp for placement in window
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

// draw player middle of minimap
static void	draw_player_center(mlx_image_t *img)
{
	int	i;
	int	j;
	int startx = (img->width / 2) - 2;
	int starty = (img->height / 2)- 2;

	i = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 6)
		{
			mlx_put_pixel(img, (startx + i), (starty + j), 0xFFA500FF);
			j++;
		}
		i++;
	}
}

// draw floors & walls based on distance to player.
// todo: make outer 2 blocks more transparent last 2 characters of hex code.
static void draw_block(t_vars *data, float tilex, float tiley, uint32_t color)
{
	int i;
	int j;

	float frac_x;
	float frac_y;
	double ignore; // needed for modf for some reason...

	// rest of float 5.7 = 0.7
	frac_x = (float)modf(data->plx, &ignore); // move to draw-small-minimap
	frac_y = (float)modf(data->ply, &ignore); // cause this is heavy computing for no reason

	// world-space to minimap-pixel, // I swear i'll make this norminette approved.
	float dx = (tilex - data->plx) * MAPSCALE - frac_x * MAPSCALE;
	float dy = (tiley - data->ply) * MAPSCALE - frac_y * MAPSCALE;

	// screen center // this can just be in drawx. wich makes it a lil unreadable.
	int centerx = data->layer1->width / 2;
	int centery = data->layer1->height / 2;

	uint32_t drawx = centerx + (int)dx; // maybe create a struct & setter function.
	uint32_t drawy = centery + (int)dy;	// for this & all needed shit above.

	// actual drawing of block lines
	i = 0;
	while (i < MAPSCALE)
	{
		j = 0;
		while (j < MAPSCALE)
		{
			if (i == 0 || j == 0 || i == MAPSCALE - 2 || j == MAPSCALE - 2)
			{
				if (drawx + i >= 0 && drawx + i < data->layer1->width &&
					drawy + j >= 0 && drawy + j < data->layer1->height)
					mlx_put_pixel(data->layer1, drawx + i, drawy + j, color);
			}
			j++;
		}
		i++;
	}
}

//draw walls/floors arround player.
void	draw_small_minimap(t_vars *data)
{
	int		offset_x;
	int		offset_y;
	float	tile_x;
	float	tile_y;
	int		map_x;
	int		map_y;

	clear_image(data->layer1);
	draw_image_outline(data->layer1, 0xE6E6FAFF); //tmp
	draw_player_center(data->layer1); //draw block in center of minimap.

	offset_y = -VIEW;
	while (offset_y <= VIEW) // count: -5 -> 5 (if define is 10)
	{
		offset_x = -VIEW;
		while (offset_x <= VIEW)
		{
			tile_x = data->plx + offset_x;
			tile_y = data->ply + offset_y;

			map_x = (int)floorf(tile_x);
			map_y = (int)floorf(tile_y);

			if (map_x >= 0 && map_x < data->mapwidth && map_y >= 0 && map_y < data->mapheight)
			{
				if (data->themap[map_y][map_x] == '1')
					draw_block(data, tile_x, tile_y, 0xFF0000FF);
				else if (data->themap[map_y][map_x] == '0')
					draw_block(data, tile_x, tile_y, 0x87CEEB08);
			}
			offset_x++;
		}
		offset_y++;
	}
}
