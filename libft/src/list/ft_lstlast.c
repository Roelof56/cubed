#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*pos;

	if (!lst)
		return (NULL);
	pos = lst;
	while (pos->next)
		pos = pos->next;
	return (pos);
}
