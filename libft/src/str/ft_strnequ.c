/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:26:27 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:26:30 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *a, char const *b, size_t n)
{
	unsigned i;

	i = 0;
	if (a && b)
		while ((*a || *b) && i++ < n)
			if (*a++ != *b++)
				return (0);
	return (1);
}
