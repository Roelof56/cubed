/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   anewmovement.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/25 14:08:55 by roelof        #+#    #+#                 */
/*   Updated: 2025/07/25 16:24:30 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "holdmydata.h"

// Check if moving by (deltax, deltay) will hit a wall
// static int	vector_collision_checker(t_vars *data, float dx, float dy)
// {
// 	float	check_x;
// 	float	check_y;

// 	check_x = data->plx + dx;
// 	check_y = data->ply + dy;

// 	if (data->themap[(int)floor(data->ply)][(int)floor(check_x)] == '1')
// 		return (1);
// 	if (data->themap[(int)floor(check_y)][(int)floor(data->plx)] == '1')
// 		return (1);
// 	return (0);
// }

// static int	vector_collision_checker(t_vars *data, float dx, float dy)
// {
// 	float	nextx;
// 	float	nexty;
// 	float	offsetx;
// 	float	offsety;
// 	float	padding;

// 	padding = 0.2f;

// 	nextx = data->plx + dx;
// 	nexty = data->ply + dy;
// 	offsetx = 0.0f;
// 	offsety = 0.0f;
// 	if (dx > 0)
// 		offsetx = padding;
// 	else if (dx < 0)
// 		offsetx = -padding;

// 	if (dy > 0)
// 		offsety = padding;
// 	else if (dy < 0)
// 		offsety = -padding;
// 	if (data->themap[(int)floor(data->ply)][(int)floor(nextx + offsetx)] == '1')
// 		return (1);
// 	if (data->themap[(int)floor(nexty + offsety)][(int)floor(data->plx)] == '1')
// 		return (1);

// 	return (0);
// }

// static int	circle_collision_checker(t_vars *data, float dx, float dy)
// {
// 	float	new_x;
// 	float	new_y;
// 	float	radius;
// 	int		i;
// 	float	angle;
// 	float	sample_x;
// 	float	sample_y;

// 	new_x = data->plx + dx;
// 	new_y = data->ply + dy;
// 	radius = 0.2f;

// 	i = 0;
// 	while (i < 8) // 8 sample points around the circle
// 	{
// 		angle = (2 * PI / 8) * i;
// 		sample_x = new_x + cos(angle) * radius;
// 		sample_y = new_y + sin(angle) * radius;
// 		if (data->themap[(int)floor(sample_y)][(int)floor(sample_x)] == '1')
// 			return (1);
// 		i += 1;
// 	}
// 	return (0);
// }

// // Move forward (W)
// static void	move_forward(t_vars *data, int speed)
// {
// 	float	dx;
// 	float	dy;

// 	dx = data->pdx / speed;
// 	dy = data->pdy / speed;
// 	if (circle_collision_checker(data, dx, dy) == 0)
// 	{
// 		data->plx += dx;
// 		data->ply += dy;
// 	}
// }

// // Move backward (S)
// static void	move_backward(t_vars *data, int speed)
// {
// 	float	dx;
// 	float	dy;

// 	dx = -data->pdx / speed;
// 	dy = -data->pdy / speed;
// 	if (circle_collision_checker(data, dx, dy) == 0)
// 	{
// 		data->plx += dx;
// 		data->ply += dy;
// 	}
// }

// // Strafe left (A)
// static void	strafe_left(t_vars *data, int speed)
// {
// 	float	dx;
// 	float	dy;

// 	dx = data->pdy / speed;
// 	dy = -data->pdx / speed;
// 	if (circle_collision_checker(data, dx, dy) == 0)
// 	{
// 		data->plx += dx;
// 		data->ply += dy;
// 	}
// }

// // Strafe right (D)
// static void	strafe_right(t_vars *data, int speed)
// {
// 	float	dx;
// 	float	dy;

// 	dx = -data->pdy / speed;
// 	dy = data->pdx / speed;
// 	if (circle_collision_checker(data, dx, dy) == 0)
// 	{
// 		data->plx += dx;
// 		data->ply += dy;
// 	}
// }

// Main movement handler
// void	move_player(t_vars *data)
// {
// 	t_keystate	state;
// 	int			speed;

// 	state = data->keystate;
// 	speed = 60;

// 	if (state.w == 1 && state.s == 1)
// 		return ;
// 	if (state.a == 1 && state.d == 1)
// 		return ;
// 	if (state.a == 1 && state.w == 0 && state.s == 0)
// 		strafe_left(data, 60);
// 	if (state.d == 1 && state.w == 0 && state.s == 0)
// 		strafe_right(data, 60);
// 	if ((state.w == 1 || state.s == 1) && (state.a == 1 || state.d == 1))
// 		speed = 80;

// 	if (state.w == 1)
// 	{
// 		if (state.a == 1)
// 			strafe_left(data, speed);
// 		else if (state.d == 1)
// 			strafe_right(data, speed);
// 		move_forward(data, speed);
// 		return ;
// 	}
// 	if (state.s == 1)
// 	{
// 		if (state.a == 1)
// 			strafe_left(data, speed);
// 		else if (state.d == 1)
// 			strafe_right(data, speed);
// 		move_backward(data, speed);
// 	}
// }
