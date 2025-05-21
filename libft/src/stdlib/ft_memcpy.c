#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int			i;
	char		*temp;

	if (!dst && !src)
		return (NULL);
	temp = (char *)dst;
	i = 0;
	while (n--)
	{
		temp[i] = ((char *) src)[i];
		i++;
	}
	return (dst);
}
