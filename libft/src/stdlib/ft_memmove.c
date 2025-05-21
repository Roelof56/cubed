#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*temp;
	char		*temp_src;

	if (!dst && !src)
		return (NULL);
	i = 0;
	temp = (char *) dst;
	temp_src = (char *) src;
	if (len == 0)
		return (temp);
	if (temp > temp_src)
		while (len--)
			temp[len] = temp_src[len];
	else
	{
		while (i < len)
		{
			temp[i] = temp_src[i];
			i++;
		}
	}
	return (temp);
}
