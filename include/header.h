/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:25 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/18 16:17:07 by rhol          ########   odam.nl         */
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

# define WIDTH 1280
# define HEIGHT 960
# define PI 3.14159
# define SCALE 32	// OG map scale

# define MAPSCALE 16	// size of wall & floor blocks.
# define VIEW 10		// ammount of blocks to draw arround player x & y

// typedef struct s_mapinfo //texture save point
// {
// 	mlx_texture_t *no;
// 	mlx_texture_t *we;
// 	mlx_texture_t *ea;
// 	mlx_texture_t *so;
// 	t_color f;
// 	t_color c;
// }				t_mapinfo;

/* map data struct */
typedef struct s_vars
{
	mlx_t			*mlx;
	char			**map_info; // texture loc & colors
	char			**themap;	// actual map
	int				mapheight;	// y columns
	int				mapwidth; // x -width = constant now.
	// t_mapinfo	textures;
	double			plx; //player x location
	double			ply; // player y location
	double			pla; // player angle -> in radians 0 - 2pi
	double			pdx; // player delta x
	double			pdy; // player delta y
	mlx_image_t		*fovlines; // minimap player fov lines go here.
	mlx_image_t		*layer1; // small minimap
}				t_vars;

/* linkedlist - for map import*/
typedef struct s_maplst
{
	char			*line;
	struct s_maplst	*next;
}					t_maplst;

/* for bresenhams line algo */
typedef struct s_line
{
	int		x1; // Start point
	int		y1;
	int		x2; // End point
	int		y2;
}			t_line;

/* colour */
typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
	int		a;
}			t_color;

/* error.c */
int			ft_strerror(char *str);
void		clean_map_info(t_vars *data);
int			clean_2dchar_array(t_vars *data, int length);

/* parser_main.c */
int			import_mapfile(t_vars *data, char *str);

/* parser_load_file.c */
int			file_to_linkedlist(int fd, t_maplst **head);

/* new_linkedlist.c */
void		ll_print_list(t_maplst *head); //delete at some point.
t_maplst	*ll_new_node(char *str);
void		ll_add_back(t_maplst **head, t_maplst *new);
int			ll_listsize(t_maplst *head);
void		ll_clean_list(t_maplst **head);

/* parser_get_mapinfo.c */
int			get_map_info(t_maplst *head, t_vars *data);

/* parser_get_map.c */
int			load_that_map(t_vars *data, t_maplst *head);

/* parser_validate_map.c */
int			validate_that_map(t_vars *data);

/* parser_validate_utils.c */
void		reset_map_fields(char **map);
int			check_map_for_invalid_chars(char **themap);
int			check_for_player(t_vars *data, char **themap);

/* parser_floodfill.c */
int			call_floodfill_thing(t_vars *data);

/* parser_printer.c */
int			print_2d_char_array(char **map, int len);
int			print_map_color(char **map, int len);

/*_ init_mlx.c _*/
int			start_mlx(t_vars *data);

/* key_input_handler.c */
void		change_player_angle(t_vars *data, int dir);
void		mouse_hook(double xpos, double ypos, void *param);
void		input_hook(void *param);

/* draw_minimap.c */
int			draw_minimap(t_vars *data);

/* draw_minimap_player.c */
// void		move_minimap_player(t_vars *vars);
// void		first_draw_minimap_player(t_vars *data);

/* draw_utils_color.c */
int			ft_get_rgba(int r, int g, int b, int a);

/* draw_fov.c */
double		degree_to_radians(double degree);
void		clear_image(mlx_image_t *img);
void		draw_fov_line(t_vars *data);

/* draw_small_minimap.c */
void	draw_small_minimap(t_vars *data);

/* parser_square_map.c */
int		make_map_square(t_vars *data);

#endif
