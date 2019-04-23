/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:22:55 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:22:57 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstpush(t_list **lst, void *content, size_t size)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	new->content = content;
	new->content_size = size;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
	return (new);
}
