/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_floodfill.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 16:52:57 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/02 16:28:36 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOLDMYDATA_H
# define HOLDMYDATA_H

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

#endif
