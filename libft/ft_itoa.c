/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 15:23:49 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/02 16:55:37 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(long int x)
{
	int	i;

	i = 0;
	if (x <= 0)
	{
		i++;
		x *= -1;
	}
	while (x > 0)
	{
		x /= 10;
		i++;
	}
	return (i);
}

static void	ft_negative(long int *nb, char *str)
{
	str[0] = '-';
	*nb *= -1;
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		len;

	nb = n;
	len = ft_length(nb);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	len--;
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
		ft_negative(&nb, str);
	while (nb > 0)
	{
		str[len] = nb % 10 + '0';
		nb /= 10;
		len--;
	}
	return (str);
}
