#include "cubed.h"
static int	check_map_extension(char *str)
{
	int		i;
	char	*type;

	i = 0;
	type = NULL;
	if (!str)
		return (1);
	if (ft_strlen(str) <= 4)
		return (1);
	while (str[i])
		i++;
	type = ft_substr(str, (i - 4), 4); //get extension (last 4 chars.)
	if (!type)
		return (ft_strerror("You encountered a malloc error."));
	if (ft_strncmp(type, ".cub", 4) != 0)
	{
		free(type);
		return (1);
	}
	free(type);
	return (0);
}

int	import_map(t_vars *vars, char *str)
{
	t_maplst	*data;
	t_maplst	*map;
	int			fd;

	data = NULL;
	map = NULL;
	if (check_map_extension(str) == 1)
		return (ft_strerror("invalid map extension. use '*.cub'"));
	if (open_that_file(str, &fd) == 1)
		return (ft_strerror("Failed to open file."));
	if (read_and_save_to_linkedlist(fd, &data, &map) == 1) //split mapinfo & map
	{
		// if there is list -> clean it here (part of it if something went wrong)
		return (ft_strerror("Faild on read_and_save_map()."));
	}
	// 	printf("\ndata from mapfile (in list form): \n");
	// 	ll_print_list(data);
	// 	printf("\nthe map (in list form): \n");
	// 	ll_print_list(map);
	if (parse_and_save_mapinfo(vars, data) != 0)	/// save mapinfo (sprites/color)
		return (ft_strerror("wrong mapinfo (colors & identifiers)")); //clean lists...
	if (parse_and_save_themap(vars, map) != 0)		// save the actual map
		return (ft_strerror("Error in map parsing")); //need to clean 2d array -> & lists
	ll_clean_list(&data); // clean both lists.
	ll_clean_list(&map);
	return (0);
}
