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

// save em in data struct t_vars *data->textures
int	save_textures_in_struct(t_textures *dest, char **arr)
{
	dest->no = mlx_load_png(arr[0]);
	if (!dest->no)
		return (ft_strerror("mlx_load_png failed on north texture\n"));
	dest->so = mlx_load_png(arr[1]);
	if (!dest->so)
		return (ft_strerror("mlx_load_png failed on south texture\n"));
	dest->we = mlx_load_png(arr[2]);
	if (!dest->we)
		return (ft_strerror("mlx_load_png failed on west texture\n"));
	dest->ea = mlx_load_png(arr[3]);
	if (!dest->ea)
		return (ft_strerror("mlx_load_png failed on east texture\n"));
	return (0);
}

// use .png or leave.
int	enforce_texture_file_extension(char **arr)
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

// check if texture file exist.
int	validate_texture_files(char **map_info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (access(map_info[i], F_OK) != 0)
		{
			i = 0;
			while (i < 4)
			{
				map_info[i][0] = '\0';
				i++;
			}
			return (1);
		}
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
	if (validate_texture_files(data->map_info) == 1)
		return (ft_strerror("loading textures."));
	if (save_textures_in_struct(&data->textures, data->map_info) == 1)
		return (ft_strerror("saving textures."));
	return (0);
}
