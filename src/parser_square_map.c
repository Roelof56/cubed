/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_square_map.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/15 12:42:00 by roelof        #+#    #+#                 */
/*   Updated: 2025/07/30 16:01:19 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// strdup but fill with spaces till desired length is reached
char	*strdup_to_len(char *s, int len)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	while (i < len)
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// find longest line in map array
// used for making map square.
static int	find_longest_line(char **map)
{
	int	i;
	int	longest;
	int	tmp;

	i = 0;
	longest = 0;
	tmp = 0;
	while (map[i])
	{
		tmp = ft_strlen(map[i]);
		if (tmp > longest)
			longest = tmp;
		i++;
	}
	return (longest);
}

// new func to make every linelen the same - Think I need for zoomed minimap.
int	make_map_square(t_vars *data)
{
	char	**new;
	int		y;
	int		longest;

	y = 0;
	longest = find_longest_line(data->themap);
	new = malloc((data->mapheight + 1) * sizeof(char *));
	if (!new)
		return (ft_strerror("Malloc failed."));
	while (y < data->mapheight)
	{
		new[y] = strdup_to_len(data->themap[y], longest);
		if (!new[y])
		{
			clean_array(new);
			return (ft_strerror("On making map square."));
		}
		y++;
	}
	new[y] = NULL;
	clean_array(data->themap);
	data->themap = new;
	data->mapwidth = longest;
	return (0);
}
