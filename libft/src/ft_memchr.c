/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:23:11 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:23:12 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned			i;
	const unsigned char	*s;

	i = 0;
	s = (const unsigned char *)src;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
			return ((void *)src + i);
		++i;
	}
	return (NULL);
}
