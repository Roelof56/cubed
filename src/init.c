#include "cubed.h"

static int load_textures(t_vars *vars)
{
	vars->tdpl = mlx_load_png("./textures/tdpl.png");
    //if ! : ret 1.
	vars->td_player = mlx_texture_to_image(vars->mlx, vars->tdpl);
    //if ! : ret 1.
    return (0);
}

// Launch the mlx instance.
int	init_program(t_vars *vars, char *mapname)
{
	vars->mlx = mlx_init(WIDTH, HEIGHT, "   :)   ", true);
	if (!vars->mlx)
		return (1);
	// if (init_some_imgs(vars) == 1) //old test(image.c)
	// 	return (ft_strerror("error loading textures"));
	if (load_textures(vars) == 1)
		return (ft_strerror("Texture could not load."));
	if (import_map(vars, mapname) == 1)
		return (ft_strerror("Error on importing map"));
	return (0);
}
