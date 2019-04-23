/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:26:38 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:26:40 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *needle, size_t size)
{
	unsigned i;
	unsigned k;

	if (!*needle)
		return ((char *)str);
	k = 0;
	while (str[k] && k < size)
	{
		i = 0;
		while (str[k + i] && str[k + i] == needle[i] && k + i < size)
		{
			if (!needle[i + 1])
				return ((char *)str + k);
			++i;
		}
		++k;
	}
	return (NULL);
}
