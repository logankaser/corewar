/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:53:04 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/22 17:57:55 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FVN-1a 64 bit.
*/

uint64_t	ft_fnv_64(const uint8_t *data, size_t size)
{
	uint64_t	hash;
	size_t		i;

	hash = 14695981039346656037ULL;
	i = 0;
	while (i < size)
	{
		hash = data[i++] ^ hash;
		hash *= 1099511628211ULL;
	}
	return (hash);
}

/*
** FVN-1a 32 bit.
*/

uint32_t	ft_fnv_32(const uint8_t *data, size_t size)
{
	uint32_t	hash;
	size_t		i;

	hash = 2166136261;
	i = 0;
	while (i < size)
	{
		hash = data[i++] ^ hash;
		hash *= 16777619;
	}
	return (hash);
}
