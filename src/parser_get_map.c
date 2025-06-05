/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_get_map.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:05:37 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/02 18:52:07 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//create 2d char array based on length of head (linked list)
static char	**create_new(t_maplst *head)
{
	char	**new;
	int		size;
	int		i;

	i = 0;
	new = NULL;
	size = ll_listsize(head) - 6;
	new = malloc((size + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (i <= size)
	{
		new[i] = NULL;
		i++;
	}
	return (new);
}

int	load_that_map(t_vars *data, t_maplst *head)
{
	int			i;
	t_maplst	*cpy;

	i = 0;
	data->mapheight = ll_listsize(head) - 6;
	cpy = head;
	data->themap = create_new(head);
	if (!data->themap)
		return (ft_strerror("failed to create 2d char array for map."));
	while (i < 6)
	{
		cpy = cpy->next;
		i++;
	}
	i = 0;
	while (i < data->mapheight)
	{
		data->themap[i] = ft_strdup(cpy->line);
		if (!data->themap[i])
			return (clean_2dchar_array(data, i));
		i++;
		cpy = cpy->next;
	}
	return (0);
}
