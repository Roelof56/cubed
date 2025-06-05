/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: roelof <roelof@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 13:00:24 by roelof        #+#    #+#                 */
/*   Updated: 2025/06/02 16:54:22 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		min;
	int		i;

	min = 1;
	res = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || \
						str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		str++;
	if (str[i] == '-')
		min = -1;
	if (str[i] == '-' || str[i] == '+')
		str++;
	while (str[i] && ft_isdigit(str[i]))
	{
		if (i >= 10 && min == 1)
			return (-1);
		if (i >= 10 && min == -1)
			return (0);
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * min);
}
