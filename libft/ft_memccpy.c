/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 13:30:28 by roelof        #+#    #+#                 */
/*   Updated: 2020/12/08 13:21:49 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d_char;
	unsigned char	*s_char;

	d_char = (unsigned char *)dest;
	s_char = (unsigned char *)src;
	i = 0;
	while (i < n && s_char[i] != (unsigned char)c)
	{
		d_char[i] = s_char[i];
		i++;
	}
	if (i == n)
		return (NULL);
	else
	{
		d_char[i] = s_char[i];
		i++;
		return (&d_char[i]);
	}
}
