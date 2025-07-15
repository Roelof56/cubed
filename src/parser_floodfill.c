/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_floodfill.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:57 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/14 22:51:03 by roelof        ########   odam.nl         */
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

static void	flood_fill(t_vars *data, int x, int y, int *retval)
{
	int	width;

	width = (int)ft_strlen(data->themap[y]);
	if (x < 0 || y < 0 || y >= data->mapheight || x >= width)
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
int	check_if_enclosed(t_vars *data)
{
	int	retval;
	int	flatx;
	int	flaty;

	retval = 0;
	flatx = (int)data->plx;
	flaty = (int)data->ply;
	data->themap[flaty][flatx] = '0';
	flood_fill(data, flatx, flaty, &retval);
	return (retval);
}
