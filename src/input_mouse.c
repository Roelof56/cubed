/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_mouse.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/22 18:53:19 by roelof        #+#    #+#                 */
/*   Updated: 2025/07/22 18:55:44 by roelof        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// a bit more smooth edition
void	mouse_hook(double xpos, double ypos, void *param)
{
	double	center;
	t_vars	*data;

	(void)ypos;
	data = (t_vars *)param;
	center = WIDTH / 2;
	if (xpos + 30 < center)
		change_player_angle(data, 0);
	else if (xpos - 30 > center)
		change_player_angle(data, 1);
	mlx_set_mouse_pos(data->mlx, center, HEIGHT / 2);
}
