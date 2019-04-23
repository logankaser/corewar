/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:26:17 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:26:20 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *a, const char *b, size_t size)
{
	unsigned i;

	i = 0;
	while ((a[i] || b[i]) && i < size)
	{
		if (a[i] != b[i])
			return (*((unsigned char *)a + i) - *((unsigned char *)b + i));
		++i;
	}
	return (0);
}
