#include "libft.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t oldsize, size_t size)
{
	void	*nptr;

	if (!ptr)
		return (NULL);
	if (oldsize == size)
		return (ptr);
	if (oldsize > size)
		size = oldsize;
	nptr = malloc(size);
	if (!nptr)
		return (free(ptr), NULL);
	ft_memcpy(nptr, ptr, oldsize);
	free(ptr);
	return (nptr);
}
