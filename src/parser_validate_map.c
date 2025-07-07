/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_validate_map.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:48 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/02 19:22:41 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// after floodfilling to '2s' -> check if there are zeros on map
static int	check_for_unreachable_tiles(t_vars *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->themap[i] != NULL)
	{
		while (data->themap[i][j] != '\0')
		{
			if (data->themap[i][j] == '0')
			{
				data->themap[i][j] = '5';
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

//new diagonal check
static void	check_diagonal_fields(char **map, int x, int y, int maph, int *ptr)
{
	if (x < 0 || y < 0 || y >= maph || x >= (int)ft_strlen(map[y]))
	{
		*ptr = 1;
		return ;
	}
	if (map[y][x] == ' ')
	{
		*ptr = 1;
		return ;
	}
	return ;
}

//new diagonal check
		// system("clear");
		// print_map_color(data->themap, data->mapheight);
		// usleep(5000); // -> in loop for animation print thing 
static int	check_for_diagonal_gaps(t_vars *data)
{
	int		i;
	int		j;
	int		retval;
	int		tmp;

	i = 0;
	j = 0;
	retval = 0;
	tmp = 0;
	while (data->themap[i] != NULL)
	{
		while (data->themap[i][j] != '\0')
		{
			if (data->themap[i][j] == '2')
			{
				data->themap[i][j] = '3';
				check_diagonal_fields(data->themap, j + 1, i + 1, data->mapheight, &retval);
				check_diagonal_fields(data->themap, j + 1, i - 1, data->mapheight, &retval);
				check_diagonal_fields(data->themap, j - 1, i + 1, data->mapheight, &retval);
				check_diagonal_fields(data->themap, j - 1, i - 1, data->mapheight, &retval);
				if (retval == 1)
				{
					tmp = 1;
					data->themap[i][j] = '5'; //tmp for colorprint
					retval = 0;
				}

			}
			j++;
		}
		j = 0;
		i++;
	}
	return (tmp);
}

// error out if no walkable tiles in map
static int	check_walkable_space(char **map)
{
	int	i;
	int	j;
	int count;

	i = 0;
	count = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0')
				count++;
			j++;
		}
		i++;
	}
	if (count <= 0)
		return (1);
	return (0);
}

// wrapper for all checker funtions for map validation.
int validate_that_map(t_vars *data)
{
	if (check_map_for_invalid_chars(data->themap) == 1)
		return (ft_strerror("Error\nInvalid char on map."));
	if (check_walkable_space(data->themap) == 1)
		return (ft_strerror("Error\nNo walkable space"));
	if (check_for_player(data, data->themap) == 1)
		return (1);
	if (call_floodfill_thing(data) == 1)
		return (ft_strerror("Error\nWalls do not enclose map."));
	if (check_for_unreachable_tiles(data) == 1)
		return (ft_strerror("Error\nUnreachable tiles in map."));
	if (check_for_diagonal_gaps(data) == 1)
		return (ft_strerror("Error\nDiagonal gap found."));
	print_map_color(data->themap, data->mapheight);
	reset_map_fields(data->themap);
	return (0);
}
