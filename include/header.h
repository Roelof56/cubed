/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:25 by rhol          #+#    #+#                 */
/*   Updated: 2025/08/01 12:18:45 by roelof        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159
# define MAPSCALE 16	// size of wall & floor blocks minimap
# define VIEW 10		// ammount of blocks to draw arround player x & y

/* colour */
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		a;
}	t_color;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	t_color			f;
	t_color			c;
}	t_textures;

/* map data struct */
typedef struct s_vars
{
	mlx_t			*mlx;
	char			**map_info; // texture loc & colors
	char			**themap;	// actual map
	int				mapheight;	// y columns
	int				mapwidth;	// x -width = constant now.
	t_textures		textures;
	double			plx; //player x location
	double			ply; // player y location
	double			pla; // player angle -> in radians 0 - 2pi
	double			pdx; // player delta x
	double			pdy; // player delta y
	mlx_image_t		*minimap;
	mlx_image_t		*minimapbg;
	mlx_image_t		*view3d;
}	t_vars;

/* linkedlist - for map import*/
typedef struct s_maplst
{
	char			*line;
	struct s_maplst	*next;
}	t_maplst;

/* for bresenhams line algo */
typedef struct s_line
{
	int		x1; // Start point
	int		y1;
	int		x2; // End point
	int		y2;
}			t_line;

typedef struct s_ray
{
	int		hit_x; // ray hit x coordinate
	int		hit_y; // ray_hit y coordinate
	double	distance; // perpedicular distance from player's position to wall
	int		side; // 0 = vertical wall (NS), 1 = horizontal (EW)
	t_line	line; // line from player to hit point (for 2D drawing)
	double	wall_hit_x;
	double	wall_hit_y;
}	t_ray;

/* parser_error.c */
int			ft_strerror(char *str);
void		clean_map_info(t_vars *data);
void		clean_textures(t_vars *data);
int			clean_array(char **cleanme);

/* parser_file_hanling.c */
int			open_and_emptycheck(char *file, int *map_fd);

/* parser_main.c */
int			check_file_extension(char *str, char *ext);
int			import_mapfile(t_vars *data, char *str);

/* parser_load_file.c */
int			file_to_linkedlist(int fd, t_maplst **head, int count);

/* new_linkedlist.c */
t_maplst	*ll_new_node(char *str);
void		ll_add_back(t_maplst **head, t_maplst *new);
int			ll_listsize(t_maplst *head);
void		ll_clean_list(t_maplst **head);

/* parser_square_map.c */
int			make_map_square(t_vars *data);

/* parser_textures.c */
int			texture_wrapper(t_vars *data);

/* parser_import_color.c */
int			get_colours(t_vars *data, char **cf);

/* parser_color_utils.c */
int			save_color_to_struct(t_vars *data, int *intarr, int c);
int			color_digit_checker(char *str);
char		*remove_whitespace_colorinput(char *str);
char		*clean_color_text(char *str);

/* parser_get_mapinfo.c */
int			get_map_info(t_maplst *head, t_vars *data);

/* parser_get_map.c */
int			load_that_map(t_vars *data, t_maplst *head);

/* parser_validate_map.c */
int			validate_that_map(t_vars *data);

/* parser_validate_utils.c */
void		set_texturetext_null(t_vars *data);
int			check_map_for_invalid_chars(char **themap);
int			check_for_player(t_vars *data, char **themap);

/* parser_floodfill.c */
void		reset_map_fields(char **map);
int			check_if_enclosed(t_vars *data);

/* init_mlx.c */
int			start_mlx(t_vars *data);

/* input.c */
void		change_player_angle(t_vars *data, int dir);
void		input_hook(void *param);

/* input_mouse.c */
void		mouse_hook(double xpos, double ypos, void *param);

/* draw_utils_bresenham.c */
void		bresenham_line(mlx_image_t *img, t_line line, uint32_t color);

/* draw_utils.c */
void		set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
int			ft_get_rgba(t_color color);
void		clear_image(mlx_image_t *img);
void		fill_image_color(mlx_image_t *img, uint32_t color);
double		normalize_angle(double angle);

/* draw_minimap_utils.c*/
void		draw_square(t_vars *data, float tilex, float tiley, uint32_t clr);
void		square_line(t_vars *data, float tilex, float tiley, uint32_t clr);
void		draw_image_outline(mlx_image_t *img, uint32_t color);
void		draw_single_fov_line(t_vars *data, double angle);

/* draw_minimap.c */
void		draw_minimap(t_vars *data);

#endif
