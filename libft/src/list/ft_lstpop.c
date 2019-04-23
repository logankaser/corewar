/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:22:50 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:22:51 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstpop(t_list **lst)
{
	t_list	*tmp;
	void	*content;

	content = NULL;
	if (*lst)
	{
		tmp = *lst;
		*lst = tmp->next;
		content = tmp->content;
		free(tmp);
	}
	return (content);
}
