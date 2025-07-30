/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_import_color.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/14 22:43:29 by roelof        #+#    #+#                 */
/*   Updated: 2025/07/30 16:18:32 by jilustre      ########   odam.nl         */
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
		return (1);
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

static int	intarray_wrapper(char **split, int *intarr)
{
	if (check_array_length(split) == 1)
		return (clean_array(split));
	convert_to_intarray(split, intarr);
	if (are_those_ints_in_range(intarr) == 1)
		return (clean_array(split));
	return (0);
}

// get color numbers from mapfile
// save em in color struct in data.
int	get_colours(t_vars *data, char **cf)
{
	char	**split;
	char	*tmp;
	int		i;
	int		intarr[3];

	i = 0;
	while (i < 2)
	{
		tmp = remove_whitespace_colorinput(cf[i]);
		if (!tmp)
			return (ft_strerror("Malloc error\n"));
		if (color_digit_checker(tmp) == 1)
			return (1);
		split = ft_split(tmp, ',');
		free(tmp);
		if (intarray_wrapper(split, intarr) == 1)
			return (1);
		if (save_color_to_struct(data, intarr, i) == 1)
			return (clean_array(split));
		i++;
		clean_array(split);
	}
	return (0);
}
