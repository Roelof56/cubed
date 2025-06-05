/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_printer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 19:06:57 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/02 19:22:46 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// don't forget makefile & header delete before turn in.
// or seperate compile rule.

#include "header.h"

//add some color
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

//tmp - delete in future.
int	print_2d_char_array(char **map, int len)
{
	int	i;

	i = 0;
	printf("-- 2d char array printer --\n");
	while (i < len)
	{
		printf("%2d: %s\n", i, map[i]);
		i++;
	}
	return (0);
}

// move somewhere with thing above -> make with 'visual validation' ofzo
int	print_map_color(char **map, int len)
{
	int	i;
	int	j;
	int	strlen;

	i = 0;
	strlen = 0;
	printf("-- the map in color --\n");
	while (i < len)
	{
		j = 0;
		strlen = ft_strlen(map[i]);
		while (j < strlen)
		{
			if (map[i][j] == '2' || map[i][j] == '3')
				printf(COLOR_GREEN "%c" COLOR_RESET, map[i][j]);
			else if (map[i][j] == '5')
				printf(COLOR_YELLOW "%c" COLOR_RESET, map[i][j]);
			else
				printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}

