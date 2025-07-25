/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/24 12:17:07 by roelof        #+#    #+#                 */
/*   Updated: 2025/07/25 13:22:08 by roelof        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "holdmydata.h"

// input 'D' - go right unless there is wall
static void	strafe_right(t_vars *data, int speed)
{
	float	new_angle;
	float	new_pdx;
	float	new_pdy;

	new_angle = data->pla + (PI / 2);
	new_angle = normalize_angle(new_angle);
	new_pdx = cos(new_angle) * 5;
	new_pdy = sin(new_angle) * 5;
	if (data->themap[(int)floor(data->ply)][(int)floor(data->plx + (new_pdx / 5))] == '0')
		data->plx += -data->pdy / speed;
	if (data->themap[(int)floor(data->ply + (new_pdy / 5))][(int)floor(data->plx)] == '0')
		data->ply += data->pdx / speed;
}


// input 'A' - go left unless there is wall
static void	strafe_left(t_vars *data, int speed)
{
	float	new_angle;
	float	new_pdx;
	float	new_pdy;

	new_angle = data->pla - (PI / 2);
	new_angle = normalize_angle(new_angle);
	new_pdx = cos(new_angle) * 5;
	new_pdy = sin(new_angle) * 5;
	if (data->themap[(int)floor(data->ply)][(int)floor(data->plx + (new_pdx / 5))] == '0')
		data->plx += data->pdy / speed;
	if (data->themap[(int)floor(data->ply + (new_pdy / 5))][(int)floor(data->plx)] == '0')
		data->ply += -data->pdx / speed;
}

// check if wall is on 1/8 angle. 
static int	collision_cheker(t_vars *data, float angle)
{
	float	new_angle;
	float	new_pdx;
	float	new_pdy;
	int		i;
	float	offset;

	i = 0;
	offset = PI / 4;
	new_angle = angle - (offset * 2);
	while (i < 3)
	{
		new_angle = new_angle + offset;
		new_angle = normalize_angle(new_angle);
		new_pdx = cos(new_angle) * 5;
		new_pdy = sin(new_angle) * 5;
		if (data->themap[(int)floor(data->ply)][(int)floor(data->plx + (new_pdx / 10))] == '1')
			return (1);
		if (data->themap[(int)floor(data->ply + (new_pdy / 10))][(int)floor(data->plx)] == '1')
			return (1);
		i += 1;
	}
	return (0);
}

static void	move_backward(t_vars *data, int speed) // is ollision checker alleen voor achteruit ?
{
	if (collision_cheker(data, data->pla + PI) == 0)
	{
		data->plx -= data->pdx / speed;
		data->ply -= data->pdy / speed;
	}
}


// new move back
// static void	move_backward(t_vars *data, int speed)
// {
// 	float	new_angle;
// 	float	new_pdx;
// 	float	new_pdy;

// 	new_angle = data->pla - PI;
// 	new_angle = normalize_angle(new_angle);
// 	new_pdx = cos(new_angle) * 5;
// 	new_pdy = sin(new_angle) * 5;
// 	if (data->themap[(int)floor(data->ply)][(int)floor(data->plx + (new_pdx / 5))] == '0')
// 		data->plx -= data->pdx / speed;
// 	if (data->themap[(int)floor(data->ply + (new_pdy / 5))][(int)floor(data->plx)] == '0')
// 		data->ply -= data->pdy / speed;
// }

// static void	move_forward(t_vars *data, int speed)
// {
// 	if (collision_cheker(data, data->pla))
// 	{
// 		data->plx += (data->pdx / speed);
// 		data->ply += (data->pdy / speed);
// 	}
// }

// include wall collision.
static void	move_forward(t_vars *data, int speed)
{
	float	xo;
	float	yo;

	xo = 0.5;
	yo = 0.5;
	if (data->pdx < 0)
		xo = -0.5;
	if (data->pdy < 0)
		yo = -0.5;
	if (data->themap[(int)floor(data->ply)][(int)floor(data->plx + xo)] == '0')
		data->plx += (data->pdx / speed);
	if (data->themap[(int)floor(data->ply + yo)][(int)floor(data->plx)] == '0')
		data->ply += (data->pdy / speed);
}

// speed is for slowing down - higher speed = slower movement.
void	move_player(t_vars *data)
{
	t_keystate	state;
	int			speed;
	
	state = data->keystate;
	speed = 40;
	if (state.w == 1 && state.s == 1)
		return ;
	if (state.a == 1 && state.d == 1)
		return ;
	if (state.a == 1 && (state.w == 0 && state.s == 0))
		strafe_left(data, 60);
	if (state.d == 1 && (state.w == 0 && state.s == 0))
		strafe_right(data, 60);
	// set speed if double key input
	if ((state.w == 1 || state.s == 1) && (state.a == 1 || state.d == 1))
		speed = 80;
	// move forward.
	if (state.w == 1)
	{
		if (state.a == 1)
			strafe_left(data, speed);	// if fail - no forward ? choppy corner problem
		else if (state.d == 1)
			strafe_right(data, speed);
		move_forward(data, speed);
		return ;
	}
	// move backward
	if (state.s == 1)
	{
		if (state.a == 1)
			strafe_left(data, speed);
		else if (state.d == 1)
			strafe_right(data, speed);
		move_backward(data, speed);
	}
}