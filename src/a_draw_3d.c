#include "header.h"

static void draw_vert_line(mlx_image_t *img, int x, int height)
{
	int j;
	int i;
	int newheight;

	i = 0;
	newheight = 100 - (height * 5); //make height, wich is line len, into wall height
	if (newheight < 10) // force minmal wall height
		newheight = 10;
	while (i < 4)
	{
		j = 0;
		while (j < newheight)
		{
			set_pixel(img, x + i, (img->height / 2) - j, 0x00FF00FF);
			j++;
		}
		i++;
	}
}


void	draw_3d_world(t_vars *data)
{
	clear_image(data->layer2);
	// printf("=> %d\n", 1080 / 60);
	for (int i = 59; i >= 0; i--)
	{
		// printf("%d: %f\n", i, data->array[i]);
		draw_vert_line(data->layer2, i * 18, (int)data->array[i]);
	}
	draw_image_outline(data->layer2, 0x00FFFFFF);

}
