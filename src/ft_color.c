#include "cubed.h"

// int	ft_get_r(int rgba)
// {
// 	return ((rgba >> 24) & 0xFF);
// }

// int	ft_get_g(int rgba)
// {
// 	return ((rgba >> 16) & 0xFF);
// }

// int	ft_get_b(int rgba)
// {
// 	return ((rgba >> 8) & 0xFF);
// }

// int	ft_get_a(int rgba)
// {
// 	return (rgba & 0xFF);
// }

// used in draw_minimap for color of walls.
int	ft_get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}