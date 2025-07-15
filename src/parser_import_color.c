/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_import_color.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/14 22:43:29 by roelof        #+#    #+#                 */
/*   Updated: 2025/07/14 22:44:22 by roelof        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// convert char **array numbers to ints.
static void	convert_to_intarray(char **base, int *array)
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
static int	check_array_length(char **split)
{
	int	i;

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
static int	are_those_ints_in_range(int *arr)
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
static int	save_to_struct(t_vars *data, int *intarr, int c)
{
	t_color	*color;

	if (c == 0)
		color = &data->textures.f;
	else if (c == 1)
		color = &data->textures.c;
	else
		return (1);
	color->r = intarr[0];
	color->g = intarr[1];
	color->b = intarr[2];
	color->a = 255;
	return (0);
}

// get color numbers from mapfile
// save em in color struct in data.
int	get_colours(t_vars *data, char **cf)
{
	char	**split;
	int		i;
	int		intarr[3];

	i = 0;
	while (i < 2)
	{
		split = ft_split(cf[i], ',');
		if (check_array_length(split) == 1)
			return (1);
		convert_to_intarray(split, intarr);
		if (are_those_ints_in_range(intarr) == 1)
			return (1);
		if (save_to_struct(data, intarr, i) == 1)
			return (1);
		i++;
	}
	return (0);
}
