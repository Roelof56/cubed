/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_caster.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/17 10:01:38 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/23 09:43:44 by jaimeilustr   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTER_H
# define RAY_CASTER_H

typedef struct s_raydir
{
	double	x;
	double	y;
}	t_raydir;

typedef struct s_step
{
	int		x;
	int		y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
}	t_step;

typedef struct s_map
{
	int	x;
	int	y;
	int	side;
}	t_map;

typedef struct s_proj
{
	double	raw_dist;
	double	proj_dist;
	double	line_height;
	int		start;
	int		end;
}	t_proj;

typedef struct s_texinfo
{
	mlx_texture_t	*tex;
	int				tex_x;
	double			step;
	double			pos;
}	t_texinfo;

typedef struct s_tex_input
{
	t_ray			*info;
	double			angle;
	t_proj			*proj;
	t_vars			*data;
	mlx_texture_t	*tex;
}	t_tex_input;

typedef struct s_render_data
{
	t_proj		*proj;
	t_texinfo	*tinfo;
	t_ray		*info;
}	t_render_data;

#endif