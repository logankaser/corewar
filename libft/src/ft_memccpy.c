/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:23:08 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:23:09 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned		i;
	unsigned char	*d;

	i = 0;
	d = (unsigned char *)dst;
	while (i < n)
	{
		d[i] = *((unsigned char *)src + i);
		if (d[i] == (unsigned char)c)
			return (dst + i + 1);
		++i;
	}
	return (NULL);
}
