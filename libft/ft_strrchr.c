/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 16:05:13 by rhol          #+#    #+#                 */
/*   Updated: 2021/01/13 11:04:03 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	cast;
	char	*p;

	cast = ((char)c);
	i = 0;
	p = NULL;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == cast)
			return ((char *)&s[i]);
		i--;
	}
	if (i == 0)
		p = (char *)&s[i];
	return (p);
}
