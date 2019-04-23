/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:26:13 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:26:14 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t size)
{
	char		*ch;
	unsigned	i;

	ch = dst;
	i = 0;
	while (*ch)
		++ch;
	while (i < size && src[i])
	{
		ch[i] = src[i];
		++i;
	}
	ch[i] = '\0';
	return (dst);
}
