#include "libft.h"

#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*pos;
	t_list	*temp;

	if (!lst)
		return ;
	pos = *lst;
	while (pos)
	{
		temp = pos->next;
		ft_lstdelone(pos, del);
		pos = temp;
	}
	*lst = NULL;
}
