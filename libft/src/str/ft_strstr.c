/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:27:00 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:27:03 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *needle)
{
	unsigned i;

	if (!*needle)
		return ((char *)str);
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] == needle[i])
		{
			if (!needle[i + 1])
				return ((char *)str);
			++i;
		}
		++str;
	}
	return (NULL);
}
