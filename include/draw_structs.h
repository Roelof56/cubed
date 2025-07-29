/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_structs.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:57 by rhol          #+#    #+#                 */
/*   Updated: 2025/07/29 09:45:41 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_STRUCTS_H
# define DRAW_STRUCTS_H
# include <stdint.h>

/* bresenham's line algorithm data storage struct, thanks norm*/
typedef struct s_stuff
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	e2;
	int	err;
}		t_stuff;

/* draw_filled block for minimap needs many vars cause of scrolling effect.*/
typedef struct s_things
{
	uint32_t	drawx;
	uint32_t	drawy;
	float		dx;
	float		dy;
	float		frac_x;
	float		frac_y;
	double		ignore;
}				t_things;

/* draw_minimap needs a bunch of variables for scrolling */
typedef struct s_mmdata
{
	float	tilex;
	float	tiley;
	int		mapx;
	int		mapy;
	int		offsetx;
	int		offsety;
}			t_mmdata;

#endif
