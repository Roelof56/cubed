/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_validate_map.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:48 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/30 16:01:42 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	if (check_for_player_duplicates(data->themap) == 1)
		return (ft_strerror("More than 1 player on map"));
	if (check_for_player(data, data->themap) == 1)
		return (ft_strerror("No player identifier on map"));
	if (check_if_enclosed(data) == 1)
		return (ft_strerror("Walls do not enclose map."));
	reset_map_fields(data->themap);
	return (0);
}
