/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 10:02:34 by jilustre      #+#    #+#                 */
/*   Updated: 2025/06/05 17:09:52 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_line	make_line(float x1, float y1, float x2, float y2)
{
	t_line	line;
	
	line.x1 = (int)(x1);
	line.y1 = (int)(y1);
	line.x2 = (int)(x2);
	line.y2 = (int)(y2);
	return (line);
}

void draw_rays(t_vars *vars)
{
	int		r; // number of rays (60 in this case for 60 degree field of view)
	float	ra = 0.0; // ray angle
	// float	rx = 0.0; // the intersection point where the ray hits something in the x axis
	// float	ry = 0.0; // the intersection point where the ray hits something in the y axis
	float	ra_rad; // ray angle in radians
	float	Tan = 0.0; // tangent of the ray angle used for calculating horizontal or vertical interestions
	float	disH = 0.0; // distance from player to the horizontal wall hit
	float	disV = 0.0; // distance from player to the vertical wall hit
	float	vx = 0.0; // final vertical wall hit x coordinates (where the vertical ray hit the wall)
	float	vy = 0.0; // final vertical wall hit y coordinates (where the vertical ray hit the wall)
	float	px = vars->plx; // player's current x position on the map
	float	py = vars->ply; // player's current y position on the map
	float	hx, hy;
	int map_width = 0;
	int map_height = 0;
	// Get map height
	while (vars->themap[map_height])
		map_height++;
	// Get map width
	map_width = ft_strlen(vars->themap[0]);
	
	r = 0;
	ra = vars->pla + 30; // Starting ray angle
	while (r < 10)
	{
		// Normalize and convert to radians
		ra = fmod(ra, 360.0f);
		if (ra < 0)
			ra += 360.0f;
		ra_rad = degree_to_radians(ra);
		Tan = tan(ra_rad);
		/*HORIZONTAL CALCULATIONS*/
		int dof = 0;
		float rx, ry, xo, yo;
		disH = 1e6;
		if (fabs(sin(ra_rad)) > 0.0001) // Avoid division by 0
		{
			if (sin(ra_rad) > 0.0f) // Looking up
			{
				ry = (((int)py / 64) * 64) - 0.0001f;
				rx = (py - ry) / Tan + px;
				yo = -64;
				xo = -yo / Tan;
			}
			else // Looking down
			{
				ry = (((int)py / 64) * 64) + 64;
				rx = (py - ry) / Tan + px;
				yo = 64;
				xo = -yo / Tan;
			}
			while (dof < 8)
			{
				int mx = (int)(rx) / 64;
				int my = (int)(ry) / 64;
				if (my >= 0 && my < map_height && mx >= 0 && mx < map_width &&
					vars->themap[my][mx] == '1')
				{
					disH = sqrtf((rx - px)*(rx - px) + (ry - py)*(ry - py));
					hx = rx;
					hy = ry;
					break;
				}
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		else
		{
			rx = px;
			ry = py;
		}
		/*VERTICAL CALCULATIONS*/
		dof = 0;
		disV = 1e6;

		if (fabs(cos(ra_rad)) > 0.0001)
		{
			if (cos(ra_rad) > 0.0f) // Looking right
			{
				rx = (((int)px / 64) * 64) + 64;
				ry = (px - rx) * Tan + py;
				xo = 64;
				yo = -xo * Tan;
			}
			else // Looking left
			{
				rx = (((int)px / 64) * 64) - 0.0001f;
				ry = (px - rx) * Tan + py;
				xo = -64;
				yo = -xo * Tan;
			}
			while (dof < 8)
			{
				int mx = (int)(rx) / 64;
				int my = (int)(ry) / 64;
				if (my >= 0 && my < map_height && mx >= 0 && mx < map_width &&
					vars->themap[my][mx] == '1')
				{
					disV = sqrtf((rx - px)*(rx - px) + (ry - py)*(ry - py));
					vx = rx;
					vy = ry;
					break;
				}
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		else
		{
			rx = px;
			ry = py;
		}

		/*DRAW NEAREST HIT*/
		float	disFinal;
		float	fx;
		float	fy;
		if (disV < disH)
		{
			disFinal = disV;
			fx = vx;
			fy = vy;
		}
		else
		{
			fx = hx;
			fy = vy;
		}
		t_line ray_line = make_line(px, py, fx, fy);
		bresenham_line(vars->td_player, ray_line, 0x00FFFF);
		ra -= 1.0; // Decrement angle (adjust if using different FOV/rays)
		r++;
	}
}
