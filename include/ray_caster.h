/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_caster.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/17 10:01:38 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/28 15:23:35 by jilustre      ########   odam.nl         */
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
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_x;
	double	delta_y;
}	t_step;

typedef struct s_map
{
	int	map_x;
	int	map_y;
	int	side;
}	t_map;

typedef struct s_proj
{
	double	raw_dist;
	double	proj_dist;
	double	line_height;
	int		pixel_start;
	int		pixel_end;
}	t_proj;

typedef struct s_tex_info
{
	mlx_texture_t	*tex;
	int				tex_x;
	double			step;
	double			pos;
}	t_tex_info;

typedef struct s_tex_input
{
	t_ray			*ray_info;
	double			angle;
	t_proj			*proj;
	t_vars			*data;
	mlx_texture_t	*tex;
}	t_tex_input;

typedef struct s_render_data
{
	t_proj		*proj;
	t_tex_info	*tex_map;
	t_ray		*ray;
}	t_render_data;

typedef struct s_render_state
{
	int				screen_w;
	int				screen_h;
	double			fov;
	double			start_angle;
	int				px;
	t_ray			ray;
	t_proj			proj;
	t_tex_info		tex_map;
	t_render_data	column;
}	t_render_state;

/* dda.c */
void			init_ray(t_vars *data, t_raydir *dir, t_map *map, double angle);
void			ini_step(t_vars *data, t_raydir *dir, t_map *map, t_step *step);
void			dda(t_vars *data, t_map *map, t_step *step);
double			calc_dis(t_vars *data, t_map *map, t_step *step, t_raydir *dir);
t_ray			build_ray(t_vars *data, t_raydir *dir, t_map *map, double dist);

/* raycaster_utils.c */
t_proj			project(t_ray *info, double angle, int screen_h, t_vars *data);
mlx_texture_t	*get_wall_texture(t_vars *data, int side, double angle);
t_tex_info		prepare_texture_info(t_tex_input *in);
void			draw_ceiling_and_floor(t_vars *data, int px, t_proj *proj);
uint32_t		pixel_texture(t_tex_info *tinfo, t_ray *info);

/* raycaster.c*/
t_ray			ray_wall(t_vars *data, double angle);
void			draw_3d_view(t_vars *data);

#endif