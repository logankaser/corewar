/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:26:23 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:26:24 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t size)
{
	unsigned i;

	i = 0;
	while (i < size && src[i])
	{
		dst[i] = src[i];
		++i;
	}
	while (i < size)
		dst[i++] = '\0';
	return (dst);
}
