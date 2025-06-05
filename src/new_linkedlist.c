/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_linkedlist.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhol <rhol@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 17:05:44 by rhol          #+#    #+#                 */
/*   Updated: 2025/06/02 17:05:45 by rhol          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// print that list _ delete at some point.
void	ll_print_list(t_maplst *head)
{
	t_maplst	*cpy;
	int			i;

	i = 0;
	cpy = NULL;
	if (!head)
		return ;
	cpy = head;
	printf("\n- print list -\n");
	while (cpy)
	{
		printf("%.2d:%s\n", i, cpy->line);
		cpy = cpy->next;
		i++;
	}
	return ;
}

// create a new node for linkedlist.
t_maplst	*ll_new_node(char *str)
{
	t_maplst	*new;

	new = malloc(sizeof(t_maplst));
	if (!new)
		return (NULL);
	new->line = str;
	new->next = NULL;
	return (new);
}

// add to back of linkedlist
void	ll_add_back(t_maplst **head, t_maplst *new)
{
	t_maplst	*cpy;

	cpy = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	cpy = *head;
	while (cpy->next != NULL)
		cpy = cpy->next;
	cpy->next = new;
	return ;
}

// return size of linked list.
int	ll_listsize(t_maplst *head)
{
	t_maplst	*cpy;
	int			count;

	cpy = NULL;
	count = 0;
	if (!head)
		return (0);
	cpy = head;
	while (cpy)
	{
		cpy = cpy->next;
		count++;
	}
	return (count);
}

// free that memory.
void	ll_clean_list(t_maplst **head)
{
	t_maplst	*cpy;
	t_maplst	*next;

	cpy = NULL;
	next = NULL;
	if (!*head)
		return ;
	cpy = *head;
	while (cpy)
	{
		next = cpy->next;
		free(cpy->line);
		free(cpy);
		cpy = next;
	}
}
