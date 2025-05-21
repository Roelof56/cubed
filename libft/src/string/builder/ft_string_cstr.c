#include "libft.h"

/**
 * Converts a string object to a C-style string.
 *
 * @param arg The string object to convert.
 * @return A C-style string representation of the string object.
 *         Returns NULL if the conversion fails.
 */
char	*ft_string_cstr(t_string *arg)
{
	char	*tmp;

	if (!ft_string_append(arg, '\0'))
		return (ft_string_free(arg), NULL);
	tmp = ft_strdup(arg->content);
	if (!tmp)
		return (ft_string_free(arg), NULL);
	return (ft_string_free(arg), tmp);
}
