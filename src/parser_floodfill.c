/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_floodfill.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:57 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/31 12:13:07 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//set 2 fields back to 0
void	reset_map_fields(char **map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '2')
				map[i][j] = '0';
			j++;
		}
		j = 0;
		i++;
	}
}

// Floodfill split y and x checks.
static void	flood_fill(t_vars *data, int x, int y, int *retval)
{
	int	width;

	if (y < 0 || y >= data->mapheight || data->themap[y] == NULL)
	{
		*retval = 1;
		return ;
	}
	width = (int)ft_strlen(data->themap[y]);
	if (x < 0 || x >= width)
	{
		*retval = 1;
		return ;
	}
	if (data->themap[y][x] == ' ')
	{
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
}

// Flood fill for unreachable space
static int	check_unreachable_space(t_vars *data)
{
	int	y;
	int	x;
	int	region_retval;

	y = 0;
	while (data->themap[y] != NULL)
	{
		x = 0;
		while (data->themap[y][x] != '\0')
		{
			if (data->themap[y][x] == '0')
			{
				region_retval = 0;
				flood_fill(data, x, y, &region_retval);
				if (region_retval == 1)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

// Wrapper for floodfill.
int	check_if_enclosed(t_vars *data)
{
	int	retval;
	int	flatx;
	int	flaty;

	flatx = (int)data->plx;
	flaty = (int)data->ply;
	retval = 0;
	data->themap[flaty][flatx] = '0';
	flood_fill(data, flatx, flaty, &retval);
	if (retval == 1)
		return (1);
	if (check_unreachable_space(data) == 1)
		return (1);
	return (0);
}
