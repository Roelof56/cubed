/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 13:00:24 by roelof        #+#    #+#                 */
/*   Updated: 2025/07/30 16:18:16 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	long	res;
	int		min;
	int		i;

	min = 1;
	res = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		str++;
	if (str[i] == '-')
		min = -1;
	if (str[i] == '-' || str[i] == '+')
		str++;
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		if (min == 1 && res > INT_MAX)
			return (-1);
		if (min == -1 && - res < INT_MIN)
			return (0);
		i++;
	}
	return ((int)(res * min));
}
