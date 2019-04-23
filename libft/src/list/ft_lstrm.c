/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:23:00 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:23:01 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrm(t_list **lst, t_list *to_rm)
{
	t_list *prev;
	t_list *item;

	if (lst)
	{
		prev = NULL;
		item = *lst;
		while (item)
		{
			if (item == to_rm)
			{
				if (prev)
					prev->next = item->next;
				else
					*lst = item->next;
				free(item->content);
				free(item);
				break ;
			}
			prev = item;
			item = item->next;
		}
	}
}
