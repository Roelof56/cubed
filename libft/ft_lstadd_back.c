/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/15 11:51:36 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/02 16:55:59 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tail;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = ft_lstlast(*lst);
	tail->next = new;
}
