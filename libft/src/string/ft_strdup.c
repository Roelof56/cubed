#include "libft.h"

#include <stdlib.h>
#include <stdio.h>

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*str;

	len = (ft_strlen(s1) + 1);
	str = (char *)malloc(len * sizeof(char));
	if (str == 0)
		return (0);
	ft_strlcpy(str, (char *)s1, len);
	return (str);
}
