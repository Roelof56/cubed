#include "libft.h"

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;
	int		length;

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	str = (char *) malloc((length + 1) * sizeof(char));
	i = 0;
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
