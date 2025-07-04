#include "header.h"


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

// new func to make every linelen the same - Think I need for zoomed minimap.
int	make_map_square(t_vars *data)
{
	char **new;
	int y = 0;
	int x = 0;
	int longest = -1;
	
	// find longest line len. 
	while (data->themap[y])
	{
		x = ft_strlen(data->themap[y]);
		if (x > longest)
			longest = x;
		y++;
	}
	// create new
	new = malloc((y + 1) * sizeof(char *));
	if (!new)
		return (ft_strerror("Error\nMalloc failed."));
	
	// copy time
	y = 0;
	while (y < data->mapheight)
	{
		new[y] = strdup_to_len(data->themap[y], longest);
		if (!new[y])
			return (ft_strerror("Error\nOn making map square."));
		y++;
	}
	new[y] = NULL;
	// clean old one.
	clean_2dchar_array(data, y + 1);
	data->themap = new;
	data->mapwidth = longest;
	return (0);
}
