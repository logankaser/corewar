/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:23:31 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/27 19:30:44 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	*ft_memset(void *m, int value, size_t n)
{
	uint8_t		*b8;
	uint64_t	*b64;
	uint64_t	fill64;

	b8 = m;
	while (n && n % 8)
		b8[--n] = (uint8_t)value;
	fill64 = (uint8_t)value;
	fill64 = fill64 << 56 | fill64 << 48 | fill64 << 40 | fill64 << 32
		| fill64 << 24 | fill64 << 16 | fill64 << 8 | fill64;
	n /= 8;
	b64 = m;
	while (n)
		b64[--n] = fill64;
	return (m);
}
