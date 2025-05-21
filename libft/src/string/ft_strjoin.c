#include "libft.h"

#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2) + 1;
	str = (char *)malloc((s1_len + s2_len) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, (char *)s1, s1_len + 1);
	ft_strlcat(&str[s1_len], (char *)s2, s2_len);
	return (str);
}
