/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 20:21:26 by roelof        #+#    #+#                 */
/*   Updated: 2025/06/02 17:00:10 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*s2)
		return ((char *)s1);
	if (!*s1 || n == 0)
		return (NULL);
	while (s1[i + j])
	{
		if (s1[i + j] == s2[j])
		{
			while (s1[i + j] == s2[j] && (i + j) < n && s2[j])
				j++;
			if (!s2[j])
				return ((char *)&s1[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
