/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 15:30:40 by rhol          #+#    #+#                 */
/*   Updated: 2020/12/08 13:21:59 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_char;
	size_t			i;

	s_char = (unsigned char *)s;
	i = 0;
	while (i < n && s_char[i] != (unsigned char)c)
		i++;
	if (i == n)
		return (NULL);
	return ((void *)&s_char[i]);
}
