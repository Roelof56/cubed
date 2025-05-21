#include "libft.h"

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*data;

	data = (void *) malloc(count * size);
	if (data == NULL)
		return (NULL);
	ft_bzero(data, count * size);
	return (data);
}
