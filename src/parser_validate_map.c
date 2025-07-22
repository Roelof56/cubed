/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_validate_map.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:48 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/22 15:28:44 by roelof        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// error out if no walkable tiles in map
static int	check_walkable_space(char **map)
{
	int	i;
	int	j;
	int	count;

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

static int	check_for_player_duplicates(char **themap)
{
	int		i;
	int		j;
	char	player;

	i = 0;
	player = '\0';
	while (themap[i] != NULL)
	{
		j = 0;
		while (themap[i][j])
		{
			if (themap[i][j] == 'N' || themap[i][j] == 'S' ||
				themap[i][j] == 'E' || themap[i][j] == 'W')
			{
				if (player == '\0')
					player = themap[i][j];
				else
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

// wrapper for all checker funtions for map validation.
// print_map_color(data->themap, data->mapheight);
int	validate_that_map(t_vars *data)
{
	if (check_map_for_invalid_chars(data->themap) == 1)
		return (ft_strerror("Invalid char on map."));
	if (check_walkable_space(data->themap) == 1)
		return (ft_strerror("No walkable space"));
	if (check_for_player_duplicates(data->themap) == 1)
		return (ft_strerror("More than 1 player on map"));
	if (check_for_player(data, data->themap) == 1)
		return (ft_strerror("No player identifier on map"));
	if (check_if_enclosed(data) == 1)
		return (ft_strerror("Walls do not enclose map."));
	reset_map_fields(data->themap);
	return (0);
}
