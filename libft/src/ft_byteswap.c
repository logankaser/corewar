/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_byteswap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:50:16 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/25 13:50:19 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint32_t	ft_byteswap4(uint32_t const u32)
{
	uint8_t data[4];

	*((uint32_t*)data) = u32;
	return (((uint32_t)data[3] << 0)
		| ((uint32_t)data[2] << 8)
		| ((uint32_t)data[1] << 16)
		| ((uint32_t)data[0] << 24));
}

uint64_t	ft_byteswap8(uint64_t const u64)
{
	uint8_t data[8];

	*((uint64_t*)data) = u64;
	return (((uint64_t)data[7])
		| ((uint64_t)data[6] << 8)
		| ((uint64_t)data[5] << 16)
		| ((uint64_t)data[4] << 24)
		| ((uint64_t)data[3] << 32)
		| ((uint64_t)data[2] << 40)
		| ((uint64_t)data[1] << 48)
		| ((uint64_t)data[0] << 56));
}
