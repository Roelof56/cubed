/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:45 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/28 18:59:15 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// check if string has file extension - char *ext. for .cub & .png
int	check_file_extension(t_vars *data, char *str, char *ext)
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
	type = ft_substr(str, (i - 4), 4);
	if (!type)
		return (ft_strerror(data, "Encountered a malloc error."));
	if (ft_strncmp(type, ext, 4) != 0)
	{
		free(type);
		return (ft_strerror(data, "invalid extension use '<name>.cub'"));
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

// maybe move map square.
int	import_mapfile(t_vars *data, char *str)
{
	int			fd;
	t_maplst	*head;

	head = NULL;
	if (check_file_extension(data, str, ".cub") == 1)
		return (1);
	if (open_that_file(str, &fd) == 1)
		return (ft_strerror(data, "Can't open file"));
	if (file_to_linkedlist(fd, &head) == 1)
		return (ft_strerror(data, "Failed to copy file to linkedlist"));
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
