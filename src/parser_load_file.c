/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_load_file.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:32 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/31 18:25:29 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// helper func to not import empty lines.
// return 0 for empty
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
	printf("Error\nMalloc failed on linkedlist creation.");
	return (1);
}

// shorten file_to_linkedlist helper func.
static int	handle_empty_line(char *line, int count)
{
	free(line);
	if (count >= 7)
		return (1);
	return (0);
}

// shorten file_to_linkedlist - let GNL finish so it can't leak
static int	let_gnl_run_out(char *line, int fd)
{
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

// read file line for line, put in linkedlist for further parsing.
int	file_to_linkedlist(int fd, t_maplst **head, int count)
{
	char		*line;
	t_maplst	*new;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_for_empty_line(line) == 0)
		{
			if (handle_empty_line(line, count) == 1)
				return (let_gnl_run_out(line, fd));
		}
		else
		{
			count++;
			new = ll_new_node(line);
			if (!new)
				return (handle_error(line, head, fd));
			ll_add_back(head, new);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
