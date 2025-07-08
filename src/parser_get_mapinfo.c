/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_get_mapinfo.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:05:30 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/08 19:21:54 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
// number is while loop
//1. skip starting whitespace.
//2. skip identifier text
//3. skip mid whitespace.
//4. get length du text
static char	*cleanup_input_mapinfo(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = NULL;
	while (str[i] == ' ' || str[i] == '\t' )
		i++;
	while (ft_isalpha(str[i]) == 1)
		i++;
	while (str[i] == ' ' || str[i] == '\t' )
		i++;
	while (str[i + j] && str[i + j] != ' ' && str[i + j] != '\t')
		j++;
	new = ft_substr(str, i, j);
	if (!new)
		return (NULL);
	return (new);
}

// check if the given identifier is valid
// return prefered place in 2d char array.
static int	check_if_valid_identifier(char *str)
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
	if (ft_strncmp(str, "F\t", 2) == 0)
		return (4);
	if (ft_strncmp(str, "C ", 2) == 0)
		return (5);
	if (ft_strncmp(str, "C\t", 2) == 0)
		return (5);
	return (-1);
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

// check if texture file exist.
static int	validate_texture_files(char **map_info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (access(map_info[i], F_OK) != 0)
		{
			printf("texture: %d does not exist\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	create_2d_char_array(t_vars *data)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(6 * sizeof(char *));
	if (!new)
		return (1);
	while (i < 6)
	{
		new[i] = NULL;
		i++;
	}
	data->map_info = new;
	return (0);
}

// save em in data struct t_vars *data->textures
static int save_textures_in_struct(t_textures *dest, char **arr)
{

	dest->no = mlx_load_png(arr[0]);
	if (!dest->no)
		return (ft_strerror("mlx_load_png failed on north texture\n"));
	dest->so = mlx_load_png(arr[1]);
	if (!dest->so)
		return (ft_strerror("mlx_load_png failed on south texture\n"));
	dest->we = mlx_load_png(arr[2]);
	if (!dest->we)
		return (ft_strerror("mlx_load_png failed on west texture\n"));
	dest->ea = mlx_load_png(arr[3]);
	if (!dest->ea)
		return (ft_strerror("mlx_load_png failed on east texture\n"));
	return (0);
}

// use .png or leave.
static int enforce_texture_file_extension(char **arr)
{
	int i;

	i = 0;
	while (i < 4) 
	{
		if (check_file_extension(arr[i], ".png") == 1)
			return (1);
		i++;
	}
	return (0);
}

/*  --- color stuff --- */
// tmp for checking ft_split result.
// static void	print_array_char(char **arr)
// {
// 	int i = 0;

// 	printf("char array:\n");
// 	while (arr[i])
// 	{
// 		printf("%d: %s\n", i, arr[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

// tmp for checking ints from color struct
// static void	print_array_int(int *arr)
// {
// 	int i = 0;

// 	printf("int array\n");
// 	while (i <  3)
// 	{
// 		printf("%d: %d\n", i, arr[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

static void print_colorstruct(t_color *color)
{
	printf("colorstruct:\n");
	printf("r: %d\n", color->r);
	printf("g: %d\n", color->g);
	printf("b: %d\n", color->b);
	printf("a: %d\n", color->a);
	printf("convert to nbr:\n");
	printf("rgba: %d\n", ft_get_rgba(color->r,color->g,color->b,color->a));
}

// convert char **array numbers to ints.
static void convert_to_intarray(char **base, int *array)
{
	int	i;

	i = 0;
	while (base[i])
	{
		array[i] = ft_atoi(base[i]);
		i++;
	}
}

// color struct needs 3 vallues.
static int check_array_length(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		printf("incorrect amount of rgb numbers\n");
		return (1);
	}
	return (0);
}

// check if color numbers from mapfile are valid.
static int are_those_ints_in_range(int *arr)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (arr[i] > 255 || arr[i] < 0)
			return (1);
		i++;
	}
	return (0);
}

// save to data struct , maybe change data for texture thing.
// c = 0 -> floor
// c = 1 -> ceiling
static int save_to_struct(t_vars *data, int *intarr, int c)
{
	t_color *color;

	if (c == 0)
		color = &data->textures.f;
	else if (c == 1)
		color = &data->textures.c;
	else
		return (1);
	color->r = intarr[0];
	color->g = intarr[1];
	color->b = intarr[2];
	color->a = 255; // moet hier nog wat mee ?
	return (0);
}

static int	get_colours(t_vars *data, char **cf)
{
	char	**split;
	int		i;
	int		intarr[3];

	i = 0;
	while (i < 2)
	{
		printf("cf %d: %s\n", i, cf[i]);
		split = ft_split(cf[i], ',');
		if (check_array_length(split) == 1)
			return (1);
		convert_to_intarray(split, intarr);
		if (are_those_ints_in_range(intarr) == 1)
		{
			printf("out of range int found\n");
			return (1);
		}

		// todo: check if numbers are within range
		if (save_to_struct(data, intarr, i) == 1)
			return (1);
		i++;
	}
	print_colorstruct(&data->textures.f);
	print_colorstruct(&data->textures.c);
	return (0);
}

// put sprites in data->mapinfo 2d char array.
int	get_map_info(t_maplst *head, t_vars *data)
{
	int		i;

	i = 0;
	if (create_2d_char_array(data) == 1)
		return (ft_strerror("Error\n2dchar array creation failed (malloc)"));
	while (i < 6)
	{
		if (check_and_save_identifier_info(head->line, data->map_info) == 1)
			return (ft_strerror("invalid mapinfo."));
		i++;
		head = head->next;
	}
	if (enforce_texture_file_extension(data->map_info) == 1)
		return (ft_strerror("Error\nOnly .png files for textures\n"));
	if (validate_texture_files(data->map_info) == 1)
		return (ft_strerror("Error\nloading textures."));
	if (save_textures_in_struct(&data->textures, data->map_info) == 1)
		return (ft_strerror("Error\nsaving textures."));
	if (get_colours(data, &data->map_info[4]) == 1)
		return (ft_strerror("Error\nLoading color"));
	return (0);
}
