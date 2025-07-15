/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_load_file.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:32 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/15 12:08:59 by roelof        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// helper func to not import empty lines.
static int	check_for_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

// split off error handling to shorten function.
static int	handle_error(char *line, t_maplst **head, int fd)
{
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ll_clean_list(head);
	return (1);
}

// read file line for line, put in linkedlist for further parsing.
int	file_to_linkedlist(int fd, t_maplst **head)
{
	char		*line;
	t_maplst	*new;

	new = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_for_empty_line(line) == 0)
			free(line);
		else
		{
			new = ll_new_node(line);
			if (!new)
				return (handle_error(line, head, fd));
			else
				ll_add_back(head, new);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
