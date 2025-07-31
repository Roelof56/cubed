/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_color_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 15:58:40 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/30 18:16:04 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// save to data struct , maybe change data for texture thing.
// c = 0 -> floor
// c = 1 -> ceiling
int	save_color_to_struct(t_vars *data, int *intarr, int c)
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

// check if isdigit skip ',' and ' '
int	color_digit_checker(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ',')
		{
			if (ft_isdigit((int)str[i]) == 0)
			{
				free(str);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

// remove ' ' & '\t' from color text mapfile.
char	*remove_whitespace_colorinput(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
		{
			if (str[i] != '\t')
			{
				result[j] = str[i];
				i++;
				j++;
			}
		}
		if (str[i] == ' ' || str[i] == '\t')
			i++;
	}
	result[j] = '\0';
	return (result);
}

// used in parser_get_map_info to diferentiate between color & texture text
char	*clean_color_text(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (ft_isalpha(str[i]) == 1)
		i++;
	while (str[i])
	{
		result[j] = str[i];
		j++;
		i++;
	}
	result[j] = '\0';
	return (result);
}
