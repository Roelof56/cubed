#include "cubed.h"

//delete @ some point in the future.
static void	print_2d_arrays(t_vars *vars) 
{
	printf("\nprint char **array mapinfo (in main)\n"); 
	int i = 0;
	while (i < 6)
	{
		printf("%d: %s\n", i, vars->map_info[i]);
		i++;
	}
	printf("\nprint char **array themap (in main)\n");
	i = 0;
	while (vars->themap[i] != NULL)
	{
		printf("%.2d: %s\n", i, vars->themap[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		return (ft_strerror("give map in argument."));
	if (init_program(&vars, argv[1]) == 1)
		return (1);
	draw_minimap(&vars);
	print_2d_arrays(&vars);
	mlx_loop_hook(vars.mlx, &input_hook, &vars);
	// mlx_loop_hook(vars.mlx, &draw_map, &vars); //tmp turn of fix img situation. or draw squares?
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
