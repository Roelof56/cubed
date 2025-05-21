#include "cubed.h"

//create 2d char array based on length of head (linked list)
char **create_new(t_maplst *head)
{
	char	**new;
	int		size;
	int		i;

	i = 0;
	new = NULL;
	size = ll_listsize(head);
	// printf("size: %d\n", size);
	new = malloc((size + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (i <= size)
	{
		// printf("set %d to null\n", i);
		new[i] = NULL;
		i++;
	}
	return (new);
}

// if convert_maplist_array fails, this cleans what was created.
static void	half_clean_array(char **array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(array[i]);
		i++;
	}
}

// put that linkedlist in an 2d char array.
int	convert_maplist_to_array(t_vars *vars, t_maplst *map)
{
	t_maplst	*cpy;
	char		**newmap;
	int			mapheight;
	int			i;

	i = 0;
	cpy = NULL;
	newmap = NULL;
	mapheight = 0;
	if (!vars || !map)
		return (ft_strerror("An argument in convert_maplist_to_array() is null :("));
	cpy = map;
	newmap = create_new(cpy);
	if (!newmap)
		return (ft_strerror("problem creating 2d char array"));
	mapheight = ll_listsize(cpy);
	while (i < mapheight)
	{
		newmap[i] = ft_strdup(cpy->line);
		if (!newmap[i])
		{
			half_clean_array(newmap, i);
			return (ft_strerror("A malloc error has happened. bye bye"));
		}
		i++;
		cpy = cpy->next;
	}
	vars->themap = newmap;
	return (0);
}
