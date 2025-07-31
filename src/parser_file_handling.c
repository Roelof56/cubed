/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_file_handling.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/31 17:56:48 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/31 18:09:22 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// empty file checker
static int	check_for_empty_file(int fd)
{
	char	*line;
	int		i;
	int		retval;

	retval = 1;
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		while (line[i])
		{
			if (line[i] != ' ')
			{
				if (line[i] != '\n')
					retval = 0;
			}
			i++;
		}
		free(line);
		line = get_next_line(fd);
		i = 0;
	}
	close(fd);
	return (retval);
}

// open file on file file descriptor
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

int	open_and_emptycheck(char *file, int *map_fd)
{
	if (open_that_file(file, map_fd) == 1)
	{
		printf("Error\nCan't open file");
		return (1);
	}
	if (check_for_empty_file(*map_fd) == 1)
	{
		printf("Error\nEmpty file");
		return (1);
	}
	if (open_that_file(file, map_fd) == 1)
	{
		printf("Error\nCan't open file");
		return (1);
	}
	return (0);
}
