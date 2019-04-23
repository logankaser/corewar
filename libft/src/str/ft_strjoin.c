/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:25:50 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:25:52 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *a, char const *b)
{
	char		*c;
	unsigned	len;

	len = (a ? ft_strlen(a) : 0) + (b ? ft_strlen(b) : 0);
	NULL_GUARD(c = malloc(len + 1));
	c[len] = '\0';
	if (a)
		while (*a)
			*c++ = *a++;
	if (b)
		while (*b)
			*c++ = *b++;
	return (c - len);
}
