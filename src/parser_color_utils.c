/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_color_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 15:58:40 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/28 16:39:25 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// check if isdigit skip ',' and ' '
int	color_digit_checker(char *str)
{
	int		i;
	
	i = 0;
	while(str[i])
	{
		if (str[i] != ',' || str[i] == ' ')
		{
			if (ft_isdigit((int)str[i]) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

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
char *clean_color_text(char *str)
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
