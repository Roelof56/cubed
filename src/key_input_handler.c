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

//todo: Find way to keep mouse in screen.
void mouse_hook(double xpos, double ypos, void *param)
{
	(void) ypos;
	(void) xpos;
	(void) param;

	t_vars			*data;
	static double	lastpos;

	data = (t_vars *)param;
	if (lastpos > xpos)
		change_player_angle(data, 0);
	if (lastpos < xpos)
		change_player_angle(data, 1);
	lastpos = xpos;
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2); // keep mouse in screen.
}

static void	handle_front_back_movement(t_vars *data, int key)
{
	float xo;
	float yo;

	xo = 0.5;
	yo = 0.5;
	if (data->pdx < 0)
		xo = -0.5;
	if (data->pdy < 0)
		yo = -0.5;
	if (key == MLX_KEY_W)
	{
		if (data->themap[(int)floor(data->ply)][(int)floor(data->plx + xo)] == '0')
			data->plx += (data->pdx / 40);
		if (data->themap[(int)floor(data->ply + yo)][(int)floor(data->plx)] == '0')
			data->ply += (data->pdy / 40);
	}
	if (key == MLX_KEY_S)
	{
		if (data->themap[(int)floor(data->ply)][(int)floor(data->plx - xo)] == '0')
			data->plx -= (data->pdx / 40);
		if (data->themap[(int)floor(data->ply - yo)][(int)floor(data->plx)] == '0')
			data->ply -= (data->pdy / 40);
	}

}

static void	handle_side_movement(t_vars *data, int key)
{
	float xo;
	float yo;
	float new_angle;
	float new_pdx;
	float new_pdy;

	xo = 0.5;
	yo = 0.5;
	if (key == MLX_KEY_D)
		new_angle = data->pla + (PI / 2);
	
	if (key == MLX_KEY_A)
		new_angle = data->pla - (PI / 2);
	
	if (new_angle > (2 * PI))
		new_angle -= (2 * PI); //make general normalize angle function, cause i do this a lot.
	if (new_angle < 0)
		new_angle += (2 * PI);

	new_pdx = cos(new_angle) * 5;
	new_pdy = sin(new_angle) * 5;

	if (new_pdx < 0)
		xo = -0.5;
	if (new_pdy < 0)
		yo = -0.5;

	if (key == MLX_KEY_D)
	{
		if (data->themap[(int)floor(data->ply)][(int)floor(data->plx + xo)] == '0')
			data->plx += -data->pdy / 60;
		if (data->themap[(int)floor(data->ply + yo)][(int)floor(data->plx)] == '0')
			data->ply += data->pdx / 60;
	}
	if (key == MLX_KEY_A)
	{
		if (data->themap[(int)floor(data->ply)][(int)floor(data->plx + xo)] == '0')
			data->plx += data->pdy / 60;
		if (data->themap[(int)floor(data->ply + yo)][(int)floor(data->plx)] == '0')
			data->ply += -data->pdx / 60;
	}

}


// temp - delete
static void print_colorstruct(t_color *color)
{
	printf("colorstruct:\n");
	printf("r: %d\n", color->r);
	printf("g: %d\n", color->g);
	printf("b: %d\n", color->b);
	printf("a: %d\n", color->a);
}

void	input_hook(void *param)
{
	t_vars	*data;

	data = (t_vars *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		handle_front_back_movement(data, MLX_KEY_W);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		handle_front_back_movement(data, MLX_KEY_S);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		handle_side_movement(data, MLX_KEY_A);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		handle_side_movement(data, MLX_KEY_D);
	// more color testing shit.
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
	{
		if (data->textures.c.r < 245)
		{
			printf("increase red\n");
			data->textures.c.r += 10;
		}
		else if (data->textures.c.r > 245)
		{
			printf("reset red\n");
			data->textures.c.r = 0;
		}
		print_colorstruct(&data->textures.c);
		fill_image_color(data->layer2, ft_get_rgba(data->textures.c));
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_G))
	{
		if (data->textures.c.g < 245)
		{
			printf("increase green\n");
			data->textures.c.g += 10;
		}
		else if (data->textures.c.g > 245)
		{
			printf("reset green red\n");
			data->textures.c.g = 0;
		}
		print_colorstruct(&data->textures.c);
		fill_image_color(data->layer2, ft_get_rgba(data->textures.c));
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_B))
	{
		if (data->textures.c.b < 245)
		{
			printf("increase blue\n");
			data->textures.c.b += 10;
		}
		else if (data->textures.c.b > 245)
		{
			printf("reset blue\n");
			data->textures.c.b = 0;
		}
		print_colorstruct(&data->textures.c);
		fill_image_color(data->layer2, ft_get_rgba(data->textures.c));
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_C))
	{
		printf("reset ceiling color struct to 0 0 0 255\n");
		data->textures.c.r = 0;
		data->textures.c.g = 0;
		data->textures.c.b = 0;
		print_colorstruct(&data->textures.c);
		fill_image_color(data->layer2, ft_get_rgba(data->textures.c));
	}
	// end new color buttons. delete later.
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		change_player_angle(data, 1);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		change_player_angle(data, 0);
}
