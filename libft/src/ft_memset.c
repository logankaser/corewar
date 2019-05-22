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

	b8 = m;
	while (n)
		b8[--n] = value;
	return (m);
}
