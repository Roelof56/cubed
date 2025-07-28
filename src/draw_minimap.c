/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/09 17:09:25 by jilustre      #+#    #+#                 */
/*   Updated: 2025/07/28 19:22:32 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "draw_structs.h"
#include "ray_caster.h"

//draw fovlines. maybe use 1 degree to rad as step ? 
static void	draw_fov_minimap(t_vars *data)
{
	double	fov;
	double	start_angle;
	double	step;
	int		i;
	double	angle;

	fov = PI / 3.0;
	start_angle = data->pla - fov / 2.0;
	step = fov / 60;
	i = 0;
	while (i < 60)
	{
		angle = start_angle + i * step;
		draw_single_fov_line(data, angle);
		i++;
	}
}

//set draw_minimap_vars - norm made me do it.
static void	set_draw_minimap_vars(t_mmdata *mmdata, float plx, float ply)
{
	mmdata->tilex = plx + mmdata->offsetx;
	mmdata->tiley = ply + mmdata->offsety;
	mmdata->mapx = (int)floorf(mmdata->tilex);
	mmdata->mapy = (int)floorf(mmdata->tiley);
}

// new - use struct.
void	draw_minimap(t_vars *data)
{
	t_mmdata	mmdata;

	clear_image(data->minimap);
	mmdata.offsety = -VIEW;
	while (mmdata.offsety <= VIEW)
	{
		mmdata.offsetx = -VIEW;
		while (mmdata.offsetx <= VIEW)
		{
			set_draw_minimap_vars(&mmdata, data->plx, data->ply);
			if (mmdata.mapx >= 0 && mmdata.mapx < data->mapwidth
				&& mmdata.mapy >= 0 && mmdata.mapy < data->mapheight)
			{
				if (data->themap[mmdata.mapy][mmdata.mapx] == '1')
					square_line(data, mmdata.tilex, mmdata.tiley, 0xFFFFFFFF);
				else if (data->themap[mmdata.mapy][mmdata.mapx] == '0')
					draw_square(data, mmdata.tilex, mmdata.tiley, 0xFFFFFF09);
			}
			mmdata.offsetx++;
		}
		mmdata.offsety++;
	}
	draw_fov_minimap(data);
	draw_image_outline(data->minimap, 0xE6E6FAFF);
}
