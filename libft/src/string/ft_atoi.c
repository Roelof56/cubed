#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		multi;
	long	answer;

	i = 0;
	multi = 1;
	answer = 0;
	if (ft_strncmp(str, "-2147483648", 11) == 0)
		return (-2147483648);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			multi = -multi;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		answer = (answer * 10) + (str[i++] - '0');
	return (answer * multi);
}
