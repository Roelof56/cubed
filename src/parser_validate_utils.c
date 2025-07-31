/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_validate_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:53 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/31 18:06:18 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// set mapinfo textuers to /0 so it wont try to clean
void	set_texturetext_null(t_vars *data)
{
	data->map_info[0][0] = '\0';
	data->map_info[1][0] = '\0';
	data->map_info[2][0] = '\0';
	data->map_info[3][0] = '\0';
}

// check if char c is allowed.
// return 0 for yes, 1 for no.
static int	char_checker(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

// check if the map contains invalid chars.
int	check_map_for_invalid_chars(char **themap)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (themap[i] != NULL)
	{
		while (themap[i][j] != '\0')
		{
			if (char_checker(themap[i][j]) == 1)
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

// save player location & angle
// data plx/y + lil offset seems like a bit of a dirty fix.
static void	save_player_location(t_vars *data, int x, int y)
{
	char	dir;

	data->plx = x + 0.51;
	data->ply = y + 0.51;
	dir = data->themap[y][x];
	if (dir == 'N')
		data->pla = (3 * PI) / 2;
	if (dir == 'E')
		data->pla = 2 * PI;
	if (dir == 'S')
		data->pla = PI / 2;
	if (dir == 'W')
		data->pla = PI;
	data->pdx = cos(data->pla) * 5;
	data->pdy = sin(data->pla) * 5;
}

//find player loc & angle. - also check for multiple
// maybe move that to parsing function- when checking for illegal chars ?
int	check_for_player(t_vars *data, char **themap)
{
	int		i;
	int		j;
	char	player;

	i = 0;
	j = 0;
	player = '\0';
	while (themap[i] != NULL)
	{
		while (themap[i][j] != '\0')
		{
			if (themap[i][j] == 'N' || themap[i][j] == 'S' ||
				themap[i][j] == 'E' || themap[i][j] == 'W')
			{
				player = themap[i][j];
				save_player_location(data, j, i);
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (player == '\0')
		return (1);
	return (0);
}
