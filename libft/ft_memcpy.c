/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:37:23 by roelof        #+#    #+#                 */
/*   Updated: 2020/12/08 13:22:16 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	void	*tmp;

	if (!dst && !src)
		return (NULL);
	tmp = dst;
	while (n > 0)
	{
		*((char *)dst) = *((char *)src);
		n--;
		dst++;
		src++;
	}
	return (tmp);
}
