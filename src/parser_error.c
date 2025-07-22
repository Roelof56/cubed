/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:53:03 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/22 14:27:33 by roelof        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// print string return 1.
int	ft_strerror(char *str)
{
	printf("%s\n", str);
	return (1);
}

// clean 2d char array **map_info in t_vars *data struct
void	clean_map_info(t_vars *data)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (data->map_info[i] != NULL)
			free(data->map_info[i]);
		i++;
	}
	free(data->map_info);
}

int	clean_2dchar_array(t_vars *data, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		free(data->themap[i]);
		i++;
	}
	free(data->themap);
	return (1);
}

// clean textures & imgs 
void	clean_textures(t_vars *data)
{
	mlx_delete_texture(data->textures.no);
	mlx_delete_texture(data->textures.so);
	mlx_delete_texture(data->textures.we);
	mlx_delete_texture(data->textures.ea);
	// mlx_delete_image(data->minimap);
	// mlx_delete_image(data->minimapbg);
	// mlx_delete_image(data->view3d);
}
