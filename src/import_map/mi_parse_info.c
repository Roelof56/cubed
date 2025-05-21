#include "cubed.h"

// check if the given identifier is valid
// return prefered place in 2d char array.
static int check_if_valid_identifier(char *str)
{
	if (ft_strncmp(str, "NO", 2) == 0)
		return (0);
	if (ft_strncmp(str, "SO", 2) == 0)
		return (1);
	if (ft_strncmp(str, "WE", 2) == 0)
		return (2);
	if (ft_strncmp(str, "EA", 2) == 0)
		return (3);
	if (ft_strncmp(str, "F ", 2) == 0)
		return (4);
	if (ft_strncmp(str, "F\t", 2) == 0) //dit moet beter kunnen
		return (4);
	if (ft_strncmp(str, "C ", 2) == 0)
		return (5);
	if (ft_strncmp(str, "C\t", 2) == 0) //dit ook
		return (5);
	return (-1);
}

static char	*cleanup_input_mapinfo(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = NULL;
	while (str[i] == ' ' || str[i] == '\t' ) //skip starting whitespace.
		i++;
	while (ft_isalpha(str[i]) == 1)	//skip identifier text
		i++;
	while (str[i] == ' ' || str[i] == '\t' ) //skip mid whitespace.
		i++;
	while (str[i + j] && str[i + j] != ' ' && str[i + j] != '\t') //get length du text
		j++;
	new = ft_substr(str, i, j); // create new clean data for the array.
	if (!new)
		return (NULL);
	return (new);
}

//	arr[0] == NO (only contains path)
//	arr[1] == SO (only contains path)
//	arr[2] == WE (only contains path)
//	arr[3] == EA (only contains path)
//	arr[4] == F  //floor - 100,100,100 (splitable)
//	arr[5] == C  //ceiling
static int	check_and_save_identifier_info(char *str, char **info)
{
	int		i;
	char	*tmp;
	int		retval;
	char	*clean_intel;

	retval = 0;
	i = 0;
	tmp = NULL;
	clean_intel = NULL;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	tmp = ft_substr(str, i, 2);
	if (!tmp)
		return (1);
	retval = check_if_valid_identifier(tmp);
	free(tmp);
	if (retval >= 0 && retval < 6)
	{
		clean_intel = cleanup_input_mapinfo(str);
		if (!clean_intel)
			return (1);
		info[retval] = clean_intel;
		return (0);
	}
	return (1);
}

//expects color as text - 255,255,255 (r,g,b)
static int	convert_str_to_colorstruct(char *colorstr, t_color *save_here)
{
	char	**split;
	int		i;

	split = NULL;
	i = 0;
	split = ft_split(colorstr, ',');
	if (!split)
		return (1);
	while (split[i])
		i++;
	if (i != 3)
	{
		ft_arrfree(split);
		return (1);
	}
	save_here->r = ft_atoi(split[0]);
	save_here->g = ft_atoi(split[1]);
	save_here->b = ft_atoi(split[2]);
	save_here->a = 255;
	return (0);
}

static int	is_valid_color(t_color cpy)
{
	if (cpy.r < 0 || cpy.r > 255)
		return (1);
	if (cpy.g < 0 || cpy.g > 255)
		return (1);
	if (cpy.b < 0 || cpy.b > 255)
		return (1);
	return (0);
}


int	parse_and_save_mapinfo(t_vars *vars, t_maplst *data)
{
	int			i;
	t_maplst	*cpy;
	char		**info;

	info = NULL;
	cpy = data;
	i = 0;
	if (!vars || !data)
		return (ft_strerror("An argument in parse_and_save_mapinfo() is null :("));
	info = create_new(data);
	if (!info)
		return (ft_strerror("problem creating 2d char array"));
	while (i < 6 && cpy != NULL)
	{
		if (check_and_save_identifier_info(cpy->line, info) !=  0)
			return (ft_strerror("invalid map info"));  
		cpy = cpy->next;
		i++;
	}
	vars->map_info = info; //is dit uberhaubt nodig -> Kan het wel naar betere data omzetten.
	// color extractor & checker
	if (convert_str_to_colorstruct(info[4], &vars->floor_color) == 1)
		return (ft_strerror("problem loading floor color"));
	if (convert_str_to_colorstruct(info[5], &vars->ceiling_color) == 1)
		return (ft_strerror("problem loading ceiling color"));
	if (is_valid_color(vars->floor_color) == 1)
		return (ft_strerror("invalid number in floor color"));
	if (is_valid_color(vars->ceiling_color) == 1)
		return (ft_strerror("invalid number in ceiling color"));
	// try to load them textures.
	// if (load_map_textures(info, &vars->dirtextures) == 1) //tmp turn off
	// 	return (ft_strerror("trouble loading textures"));
	// else 
	// {
	// 	mlx_image_t *tmp;							//tmp check if texture loading goes good.
	// 	tmp = mlx_texture_to_image(vars->mlx, vars->dirtextures.n_texture);
	// 	mlx_image_to_window(vars->mlx, tmp, (WIDTH / 2 - 64), 10);
	// 	tmp = mlx_texture_to_image(vars->mlx, vars->dirtextures.s_texture);
	// 	mlx_image_to_window(vars->mlx, tmp, (WIDTH / 2 - 64), 300);
		
	// 	tmp = mlx_texture_to_image(vars->mlx, vars->dirtextures.e_texture);
	// 	mlx_image_to_window(vars->mlx, tmp, (((WIDTH / 4) * 3)), 100);
	// 	tmp = mlx_texture_to_image(vars->mlx, vars->dirtextures.w_texture);
	// 	mlx_image_to_window(vars->mlx, tmp, (WIDTH / 4) - 64, 100);
	// }
	return (0);
}
