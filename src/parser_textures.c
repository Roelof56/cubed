/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_textures.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <rhol@student.codam.nl>   	          +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/14 18:24:12 by roelof        #+#    #+#                 */
/*   Updated: 2025/07/14 18:24:14 by roelof        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// save textures is shorter now.
static void	load_error_clean(t_textures *dest)
{
	mlx_delete_texture(dest->no);
	mlx_delete_texture(dest->so);
	mlx_delete_texture(dest->we);
}

// save em in data struct t_vars *data->textures
static int	save_textures_in_struct(t_textures *dest, char **arr)
{
	dest->no = mlx_load_png(arr[0]);
	if (!dest->no)
	{
		return (1);
	}
	dest->so = mlx_load_png(arr[1]);
	if (!dest->so)
	{
		mlx_delete_texture(dest->no);
		return (1);
	}
	dest->we = mlx_load_png(arr[2]);
	if (!dest->we)
	{
		mlx_delete_texture(dest->no);
		mlx_delete_texture(dest->so);
		return (1);
	}
	dest->ea = mlx_load_png(arr[3]);
	if (!dest->ea)
	{
		load_error_clean(dest);
		return (1);
	}
	return (0);
}

// use .png or leave.
static int	enforce_texture_file_extension(char **arr)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (check_file_extension(arr[i], ".png") == 1)
			return (1);
		i++;
	}
	return (0);
}

int	texture_wrapper(t_vars *data)
{
	if (enforce_texture_file_extension(data->map_info) == 1)
	{
		set_texturetext_null(data);
		return (1);
	}
	if (save_textures_in_struct(&data->textures, data->map_info) == 1)
	{
		set_texturetext_null(data);
		return (1);
	}
	return (0);
}
