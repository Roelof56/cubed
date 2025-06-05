/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_floodfill.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:57 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/03 16:28:36 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// flood fill walkable tiles same as below with old comments & print animation.
// static void flood_fill(char **map, int x, int y, int mapheight, int *retval)
// {
// 	if (x < 0 || y < 0 || y >= mapheight || x >= (int)ft_strlen(map[y]))
// 	{
// 		map[y][x] = '5'; //tmp for animation.
// 		*retval = 1;
// 		return ;
// 	}
// 	if (map[y][x] != '0')
// 		return ;

// 	map[y][x] = '2'; // mark visited

// 	system("clear"); //tmp for animation.
// 	print_map_color(map, mapheight);
// 	usleep(5000); // tmp for animation.

// 	flood_fill(map, x + 1, y, mapheight, retval); //east
// 	flood_fill(map, x - 1, y, mapheight, retval); //west
// 	flood_fill(map, x, y + 1, mapheight, retval); //south
// 	flood_fill(map, x, y - 1, mapheight, retval); //North
// 	// flood_fill(map, x+1, y+1, mapheight, retval); //southeast //old 8way
// 	// flood_fill(map, x+1, y-1, mapheight, retval); //northeast
// 	// flood_fill(map, x-1, y+1, mapheight, retval); //zuidwest
// 	// flood_fill(map, x-1, y-1, mapheight, retval); //noordwest
// 	return ;
// }

//floodfill walkable tiles
	// system("clear");
	// print_map_color(data->themap, data->mapheight);
	// usleep(5000); //-> for animation print
static void	flood_fill(t_vars *data, int x, int y, int *retval)
{
	if (x < 0 || y < 0 || \
		y >= data->mapheight || x >= (int)ft_strlen(data->themap[y]))
	{
		data->themap[y][x] = '5';
		*retval = 1;
		return ;
	}
	if (data->themap[y][x] != '0')
		return ;
	data->themap[y][x] = '2';
	flood_fill(data, x + 1, y, retval);
	flood_fill(data, x - 1, y, retval);
	flood_fill(data, x, y + 1, retval);
	flood_fill(data, x, y - 1, retval);
	return ;
}

// Wrapper for floodfill.
int	call_floodfill_thing(t_vars *data)
{
	int	retval;
	int flatx;
	int flaty;

	retval = 0;
	flatx = (int)data->plx;
	flaty = (int)data->ply;
	data->themap[flaty][flatx] = '0';
	flood_fill(data, flatx, flaty, &retval);
	return (retval);
}
