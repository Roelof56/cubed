#include "header.h"

# define MAPSCALE 16
# define VIEW 6

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
	frac_x = (float)modf(data->plx, &ignore);
	frac_y = (float)modf(data->ply, &ignore);

	// world-space to minimap-pixel, deze naamgeveing is dom.
	float dx = (tilex - data->plx) * MAPSCALE - frac_x * MAPSCALE;
	float dy = (tiley - data->ply) * MAPSCALE - frac_y * MAPSCALE;

	// screen center
	int centerx = data->layer1->width / 2;
	int centery = data->layer1->height / 2;

	uint32_t drawx = centerx + (int)dx;
	uint32_t drawy = centery + (int)dy;

	// draw a border square
	i = 0;
	while (i < MAPSCALE)
	{
		j = 0;
		while (j < MAPSCALE)
		{
			if (i == 0 || j == 0 || i == MAPSCALE - 1 || j == MAPSCALE - 1)
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
void	a_test(t_vars *data)
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
	while (offset_y <= VIEW) // count: -3 -> 3
	{
		offset_x = -VIEW;
		while (offset_x <= VIEW)
		{
			tile_x = data->plx + offset_x;
			tile_y = data->ply + offset_y;

			map_x = (int)tile_x;
			map_y = (int)tile_y;

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


// void	a_test(t_vars *data)
// {
// 	clear_image(data->layer1);
// 	draw_image_outline(data->layer1, 0xE6E6FAFF);
// 	draw_player_center(data->layer1);

// 	int		offset_y = -5;
// 	while (offset_y <= 5)
// 	{
// 		int offset_x = -5;
// 		while (offset_x <= 5)
// 		{
// 			// target world tile
// 			int tile_x = (int)floorf(data->plx) + offset_x;
// 			int tile_y = (int)floorf(data->ply) + offset_y;

// 			// stay inside map bounds
// 			if (tile_x >= 0 && tile_x < data->mapwidth &&
// 				tile_y >= 0 && tile_y < data->mapheight)
// 			{
// 				char tile = data->themap[tile_y][tile_x];

// 				if (tile == '1')
// 					draw_block(data, tile_x, tile_y, 0xFF0000FF); // wall
// 				else
// 					draw_block(data, tile_x, tile_y, 0x87CEEB09); // floor
// 			}
// 			offset_x++;
// 		}
// 		offset_y++;
// 	}
// }

// new minimap drawn from player.
// void	a_test(t_vars *data)
// {
// 	draw_image_outline(data->layer1, 0xE6E6FAFF);
// 	draw_player_center(data->layer1);
	
	// int i = 0;
	// int j = 0;
	// double why; //needed by modf for some reason
	// float player_offsetx = (float)modf(data->plx, &why);
	// float player_offsety = (float)modf(data->ply, &why);
	// printf("player_offsetx = %f\n", player_offsetx);
	// printf("player_offsety = %f\n", player_offsety);

	// // calculate left tile's position
	// float left_tile_x = floorf(data->plx) - 1;
	// float left_tile_y = floorf(data->ply);

	// // bounds check
	// if (left_tile_x >= 0 && left_tile_x < data->mapwidth &&
	// 	left_tile_y >= 0 && left_tile_y < data->mapheight)
	// {
	// 	if (data->themap[(int)left_tile_y][(int)left_tile_x] == '1')
	// 		draw_block(data, left_tile_x, left_tile_y, 0xFF0000FF); // red wall
	// 	else
	// 		draw_block(data, left_tile_x, left_tile_y, 0x87CEEBFF); // blue floor

	// 	if (data->themap[(int)left_tile_y][(int)left_tile_x - 1] == '1')
	// 		draw_block(data, left_tile_x - 1, left_tile_y, 0xFF0000FF); // red wall
	// 	else
	// 		draw_block(data, left_tile_x - 1, left_tile_y, 0x87CEEBFF); // blue floor
		
	// 	if (data->themap[(int)left_tile_y][(int)left_tile_x - 2] == '1')
	// 		draw_block(data, left_tile_x - 2, left_tile_y, 0xFF0000FF); // red wall
	// 	else
	// 		draw_block(data, left_tile_x - 2, left_tile_y, 0x87CEEBFF); // blue floor

	// 	if (data->themap[(int)left_tile_y][(int)left_tile_x - 2] == '1')
	// 		draw_block(data, left_tile_x - 2, left_tile_y, 0xFF0000FF); // red wall
	// 	else
	// 		draw_block(data, left_tile_x - 2, left_tile_y, 0x87CEEBFF); // blue floor
	// }

	// while (i < VIEW)
	// {
		// if (data->themap[(int)floor(data->ply) - 1][(int)floor(data->plx)] == '1') // left
		// 	draw_block(data->layer1, data->plx - 1, data->ply, 0xFF0000FF);
		// else
		// 	draw_block(data->layer1, data->plx - 1, data->ply, 0xADD8E6FF);
		// i++;
	// }
// }
