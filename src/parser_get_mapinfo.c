/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_get_mapinfo.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:05:30 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/14 18:26:04 by roelof        ########   odam.nl         */
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
