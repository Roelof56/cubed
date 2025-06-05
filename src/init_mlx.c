#include "header.h"

// start mlx save in data struct.
int	start_mlx(t_vars *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "   :)   ", true);
	if (!data->mlx)
		return (1);
	return (0);
}

