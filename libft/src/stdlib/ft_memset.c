#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*p;
	unsigned long	i;

	p = (char *) b;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (p);
}
