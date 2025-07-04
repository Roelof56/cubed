/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:45 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/18 15:44:43 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// move to parser_utils ofzo ?
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
	type = ft_substr(str, (i - 4), 4);
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

static int	open_that_file(char *file, int *map_fd)
{
	int	fd;

	fd = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		*map_fd = -1;
		return (1);
	}
	*map_fd = fd;
	return (0);
}

int	import_mapfile(t_vars *data, char *str)
{
	int			fd;
	t_maplst	*head;

	head = NULL;
	if (check_map_extension(str) == 1)
		return (ft_strerror("Error\nnvalid extension use '<name>.cub'"));
	if (open_that_file(str, &fd) == 1)
		return (ft_strerror("Error\nCan't open file"));
	if (file_to_linkedlist(fd, &head) == 1)
		return (ft_strerror("Error\nFailed to copy file to linkedlist"));
	if (get_map_info(head, data) == 1)
	{
		ll_clean_list(&head);
		clean_map_info(data);
		return (1);
	}
	if (load_that_map(data, head) == 1)
	{
		ll_clean_list(&head);
		clean_map_info(data);
		return (1);
	}
	if (validate_that_map(data) == 1)
	{
		clean_map_info(data);
		clean_2dchar_array(data, (ll_listsize(head) - 6));
		ll_clean_list(&head);
		return (1);
	}
	if (make_map_square(data) == 1) // maybe insert in map validation or loading.
	{
		clean_map_info(data);
		clean_2dchar_array(data, (ll_listsize(head) - 6));
		ll_clean_list(&head);
		return (1);
	}
	ll_clean_list(&head);
	return (0);
}
