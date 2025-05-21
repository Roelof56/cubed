#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

t_list	*ft_lstadd_back_content(t_list **lst, void *content)
{
	t_list	*last;
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		return (NULL);
	if (!*lst)
	{
		*lst = new;
		return (*lst);
	}
	last = ft_lstlast(*lst);
	last->next = new;
	return (*lst);
}
