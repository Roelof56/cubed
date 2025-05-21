#include "cubed.h"

int	open_that_file(char *file, int *map_fd)
{
	int fd;

	fd = 0;
	fd = open(file, O_RDONLY);
	// printf("fd: %d\n", fd);
	if (fd == -1)
		return (1);
	*map_fd = fd;
	return (0);
}

int	read_and_save_to_linkedlist(int fd, t_maplst **info_head, t_maplst **map_head)
{
	char		*line;
	int			count_info;
	t_maplst	*new;
	char		*new_line;

	count_info = 0;
	new = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strlen(line) == 1)	// skip \n lines -> check met whitespace.
			free(line);
		else
		{
			new_line = ft_substr(line, 0, (ft_strlen(line) - 1));
			if (!new_line)
			{
				free(line);
				return (1);
			}
			new = ll_new_node(new_line); // if !new -> do something.
			free(line);
			if (count_info <= 5)
			{
				ll_add_back(info_head, new);
				count_info++;
			}
			else
				ll_add_back(map_head, new);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

