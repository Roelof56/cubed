/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/22 18:56:16 by roelof        #+#    #+#                 */
/*   Updated: 2025/07/25 16:31:39 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// maybe chang angle ammount.
void	change_player_angle(t_vars *data, int dir)
{
	if (dir == 1)
	{
		data->pla += 0.04;
		if (data->pla > (2 * PI))
			data->pla += (2 * PI);
	}
	else
	{
		data->pla -= 0.04;
		if (data->pla < 0)
			data->pla = (2 * PI);
	}
	data->pdx = cos(data->pla) * 5;
	data->pdy = sin(data->pla) * 5;
}

// wall collision movent check with offset in direction if tile is free
static void	handle_front_back_movement(t_vars *data, int key, char **map)
{
	float	xo;
	float	yo;

	xo = 0.5;
	yo = 0.5;
	if (data->pdx < 0)
		xo = -0.5;
	if (data->pdy < 0)
		yo = -0.5;
	if (key == MLX_KEY_W)
	{
		if (map[(int)floor(data->ply)][(int)floor(data->plx + xo)] == '0')
			data->plx += (data->pdx / 40);
		if (map[(int)floor(data->ply + yo)][(int)floor(data->plx)] == '0')
			data->ply += (data->pdy / 40);
	}
	if (key == MLX_KEY_S)
	{
		if (map[(int)floor(data->ply)][(int)floor(data->plx - xo)] == '0')
			data->plx -= (data->pdx / 40);
		if (map[(int)floor(data->ply - yo)][(int)floor(data->plx)] == '0')
			data->ply -= (data->pdy / 40);
	}
}

// input 'D'
static void	handle_right_movement(t_vars *data)
{
	float	xo;
	float	yo;
	float	new_angle;
	float	new_pdx;
	float	new_pdy;

	xo = 0.5;
	yo = 0.5;
	new_angle = data->pla + (PI / 2);
	new_angle = normalize_angle(new_angle);
	new_pdx = cos(new_angle) * 5;
	new_pdy = sin(new_angle) * 5;
	if (new_pdx < 0)
		xo = -0.5;
	if (new_pdy < 0)
		yo = -0.5;
	if (data->themap[(int)floor(data->ply)][(int)floor(data->plx + xo)] == '0')
		data->plx += -data->pdy / 60;
	if (data->themap[(int)floor(data->ply + yo)][(int)floor(data->plx)] == '0')
		data->ply += data->pdx / 60;
}

// input 'A'
static void	handle_left_movement(t_vars *data)
{
	float	xo;
	float	yo;
	float	new_angle;
	float	new_pdx;
	float	new_pdy;

	xo = 0.5;
	yo = 0.5;
	new_angle = data->pla - (PI / 2);
	new_angle = normalize_angle(new_angle);
	new_pdx = cos(new_angle) * 5;
	new_pdy = sin(new_angle) * 5;
	if (new_pdx < 0)
		xo = -0.5;
	if (new_pdy < 0)
		yo = -0.5;
	if (data->themap[(int)floor(data->ply)][(int)floor(data->plx + xo)] == '0')
		data->plx += data->pdy / 60;
	if (data->themap[(int)floor(data->ply + yo)][(int)floor(data->plx)] == '0')
		data->ply += -data->pdx / 60;
}

// handle keyboard input.
void	input_hook(void *param)
{
	t_vars	*data;

	data = (t_vars *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		handle_front_back_movement(data, MLX_KEY_W, data->themap);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		handle_front_back_movement(data, MLX_KEY_S, data->themap);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		handle_left_movement(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		handle_right_movement(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		change_player_angle(data, 1);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		change_player_angle(data, 0);
}
