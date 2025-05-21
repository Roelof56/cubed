#include "cubed.h"

// save x, y coordinates & player starting angle
static void	save_player_loc(t_vars *vars, int i, int j, char dir)
{
	if (dir == 'N')
		vars->pl_angle = 270;
	if (dir == 'E')
		vars->pl_angle = 0;
	if (dir == 'S')
		vars->pl_angle = 90;
	if (dir == 'W')
		vars->pl_angle = 180;
	vars->pl_x = j;
	vars->pl_y = i;
	printf("player(x,y): %f,%f", vars->pl_x, vars->pl_y);
}

//find player loc & angle. - also check for multiple
// maybe move that to parsing function- when checking for illegal chars ?
static int	check_for_player(t_vars *vars, char **themap)
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
			if (themap[i][j] == 'N' || themap[i][j] == 'S' || themap[i][j] == 'E' || themap[i][j] == 'W')
			{
				if (player == '\0')
				{
					player = themap[i][j];
					save_player_loc(vars, i, j, player);
				}
				else
					return (ft_strerror("more than 1 player character"));
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (player == '\0')
		return (ft_strerror("no player character found on map"));
	return (0);
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

// check if the map contains invalid chars. //add check for double player char here ?
static int	check_for_invalid_chars(char **themap)
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

// + convert list to array.
// + check for invalid chars
// + check if only 1 play identifier is there.
// - time to check for walls ofzo.
int	parse_and_save_themap(t_vars *vars, t_maplst *map)
{
	if (convert_maplist_to_array(vars, map) == 1)
		return (1); // moet hier iets van cleaning? denkt wel ?
	if (check_for_invalid_chars(vars->themap))
		return (ft_strerror("Invalid character on the map.")); //clean 
	if (check_for_player(vars, vars->themap) == 1)
		return (ft_strerror("Invalid map - something about player indicator")); //also clean.
	
	return (0);
}
