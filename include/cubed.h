#ifndef CUBED_H
# define CUBED_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <math.h>

#define WIDTH 1280
#define HEIGHT 960
// #define WIDTH 640
// #define HEIGHT 480

#define BPP sizeof(int32_t)
#define TWIDTH 32  //tmp
#define THEIGHT 32 //tmp

/* colour */
typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
	int		a;
}			t_color;

/* for bresenhams algo */
typedef struct s_line
{
	int		x1; // Start point
	int		y1;
	int		x2; // End point
	int		y2;
}			t_line;

//add struct for mapinfo things (sprites & colors)
// typedef struct s_mapinfo
// {
	// t_color		floor_color;
	// t_color		ceiling_color;
	// mlx_image_t	*n_texture;
	// mlx_image_t	*s_texture;
	// mlx_image_t	*e_texture;
	// mlx_image_t	*w_texture;
// }					t_mapinfo;

// typedef struct	s_textures //hier moet ik imgs van maken. => ja ?
// {
	// mlx_image_t		*td_player; //dit errorde ?
	// mlx_texture_t	*n_texture;
	// mlx_texture_t	*s_texture;
	// mlx_texture_t	*e_texture;
	// mlx_texture_t	*w_texture;
// }				t_texture;

/* main data struct */
typedef struct	s_vars
{
	mlx_t			*mlx;
	mlx_image_t		*image; //contains face.
	mlx_image_t		*td_player; //move somewhere.
	mlx_texture_t 	*tdpl;
	mlx_image_t		*square;
	char			**themap;
	char			**map_info; //uitsplitsen naar sprites & colours. hier heb ik weinig aan.
	// t_mapinfo	mapinf;
	t_color			floor_color;
	t_color			ceiling_color;
	// t_texture		dirtextures;
	double			pl_x;
	double			pl_y;
	double			pl_angle; // 0/360 = east
	double			pl_fov; // field of view.
}				t_vars;

/* map import struct */
typedef struct	s_maplst
{
	char			*line;
	struct s_maplst	*next;
}					t_maplst;


/* main.c */
void		input_hook(void *param);
int			main(int argc, char **argv);

/* input_handler.c */
void		input_hook(void *param);

/* init.c */
int			init_program(t_vars *vars, char *mapname);

/* draw_minimap.c */
int			ft_strerror(char *str);
int			draw_minimap(t_vars *vars); //weird place
void		mm_player_img_loc_change(t_vars *vars);

/* image.c */
// void		change_img_to_color(mlx_image_t *image, t_color color); //unused.

/* ft_color.c */
int			ft_get_rgba(int r, int g, int b, int a);

/* draw_player_one.c */
double		degree_to_radians(double degree);
void		draw_line_bresenham(mlx_image_t *img, double angle);
void		draw_minimap_player(t_vars *vars);

/* import_map */
/* file handling.c */
int			open_that_file(char *file, int *map_fd);
int			read_and_save_to_linkedlist(int fd, t_maplst **info_head, t_maplst **map_head);

/* mi_main_import.c */
int			import_map(t_vars *vars, char *str);

/* mi_parse_map.c */
int			parse_and_save_themap(t_vars *vars, t_maplst *map);

/* mi_infodata.c */
int			parse_and_save_mapinfo(t_vars *vars, t_maplst *data);

/* mi_llist_to_array.c */
char		**create_new(t_maplst *head);
int			convert_maplist_to_array(t_vars *vars, t_maplst *map);

/* linkedlist */
/* linkedlist.c */
void		ll_print_list(t_maplst *head); //delete at some point.
t_maplst	*ll_new_node(char *str);
void		ll_add_back(t_maplst **head, t_maplst *new);
int			ll_listsize(t_maplst *head);
void		ll_clean_list(t_maplst **head);

#endif
