#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;
	t_list	*obj;

	i = 0;
	obj = lst;
	while (obj)
	{
		obj = obj->next;
		i++;
	}
	return (i);
}
