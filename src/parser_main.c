/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:45 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/30 19:14:06 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// check if string has file extension - char *ext. for .cub & .png
int	check_file_extension(char *str, char *ext)
{
	int		i;
	char	*type;

	i = 0;
	type = NULL;
	if (!str)
		return (1);
	while (str[i])
		i++;
	if (i < 5)
	{
		printf("Error\nWrong File extension\n");
		return (1);
	}
	type = ft_substr(str, (i - 4), 4);
	if (!type)
		return (1);
	if (ft_strncmp(type, ext, 4) != 0)
	{
		free(type);
		printf("Error\nWrong File extension\n");
		return (1);
	}
	free(type);
	return (0);
}

// handle cleaning for import_mapfile
// from get_map_info & everything below it.
static int	error_clean(t_vars *data, t_maplst **head, int len)
{
	ll_clean_list(head);
	clean_textures(data);
	clean_map_info(data);
	if (len > 0)
		clean_array(data->themap);
	return (1);
}

// 
static int	check_for_empty_file(int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '\n')
				return (0);
		}
		free(line);
		line = get_next_line(fd);
		i = 0;
	}
	return (1);
}

// maybe move map square.
int	import_mapfile(t_vars *data, char *str)
{
	int			fd;
	t_maplst	*head;

	head = NULL;
	if (check_file_extension(str, ".cub") == 1)
		return (error_clean(data, &head, 0));
	if (open_that_file(str, &fd) == 1)
	{
		printf("Error\nCan't open file\n");
		return (error_clean(data, &head, 0));
	}
	if (check_for_empty_file(fd) == 1)
		return (error_clean(data, &head, 0));
	if (file_to_linkedlist(fd, &head, 0) == 1)
		return (error_clean(data, &head, 0));
	if (get_map_info(head, data) == 1)
		return (error_clean(data, &head, 0));
	if (load_that_map(data, head) == 1)
		return (error_clean(data, &head, 0));
	if (validate_that_map(data) == 1)
		return (error_clean(data, &head, (ll_listsize(head) - 6)));
	if (make_map_square(data) == 1)
		return (error_clean(data, &head, (ll_listsize(head) - 6)));
	ll_clean_list(&head);
	return (0);
}
