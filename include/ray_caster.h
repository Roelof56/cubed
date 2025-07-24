/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_caster.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/17 10:01:38 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/24 10:23:44 by jilustre      ########   odam.nl         */
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

typedef struct s_render_state
{
	int				screen_w;
	int				screen_h;
	double			fov;
	double			start_a;
	int				px;
	t_ray			info;
	t_proj			proj;
	t_texinfo		tinfo;
	t_render_data	rdata;
}	t_render_state;

void	init_structs(t_vars *data, t_raydir *dir, t_map *map, double angle);
void	init_step(t_vars *data, t_raydir *dir, t_map *map, t_step *step);
void	dda(t_vars *data, t_map *map, t_step *step);
double	calc_dist(t_vars *data, t_map *map, t_step *step, t_raydir *dir);
t_ray	build_ray(t_vars *data, t_raydir *dir, t_map *map, double dist);
t_ray	ray_wall(t_vars *data, double angle);

#endif