/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:22:41 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:22:43 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *head;
	t_list *current;
	t_list *prev;

	NULL_GUARD((lst && f));
	prev = NULL;
	head = f(ft_lstnew(lst->content, lst->content_size));
	current = head;
	lst = lst->next;
	while (lst)
	{
		prev = current;
		current = f(ft_lstnew(lst->content, lst->content_size));
		prev->next = current;
		lst = lst->next;
	}
	return (head);
}
