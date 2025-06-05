/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 13:41:05 by roelof        #+#    #+#                 */
/*   Updated: 2025/06/02 17:00:26 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_start(char const *str, char const *set)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(set, str[i]))
		i++;
	return (i);
}

static int	ft_find_end(char const *str, char const *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] && ft_strchr(set, str[i]))
		i--;
	return (i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(set) == 0)
		return (ft_strdup((char *)s1));
	else
	{
		start = ft_find_start(s1, set);
		if ((size_t)start >= ft_strlen(s1))
			return (ft_strdup(""));
		end = ft_find_end(s1, set);
	}
	dest = ft_substr(s1, start, (end - start + 1));
	if (dest == NULL)
		return (NULL);
	return (dest);
}
