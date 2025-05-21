#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*pos;

	if (!lst)
		return ;
	pos = lst;
	while (pos)
	{
		if (pos)
			f(pos->content);
		pos = pos->next;
	}
}
