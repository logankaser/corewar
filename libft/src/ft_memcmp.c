/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:23:15 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/27 20:29:55 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const uint8_t	*a;
	const uint8_t	*b;
	unsigned		i;

	a = s1;
	b = s2;
	i = 0;
	if (n < 1)
		return (0);
	while (i < n)
	{
		if (a[i] < b[i])
			return (a[i] - b[i]);
		if (a[i] > b[i])
			return (a[i] - b[i]);
		++i;
	}
	return (0);
}
