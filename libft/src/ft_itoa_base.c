/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:22:01 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:22:03 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa_base(intmax_t nbr, char *base_str, unsigned base)
{
	intmax_t	n;
	unsigned	digits;
	char		*str;

	digits = (nbr <= 0);
	n = nbr;
	while (n)
	{
		n /= base;
		++digits;
	}
	NULL_GUARD(str = malloc(digits + 1));
	str[digits--] = '\0';
	n = nbr;
	while (digits)
	{
		str[digits] = base_str[nbr < 0 ? (nbr % base) * -1 : nbr % base];
		nbr /= base;
		--digits;
	}
	str[0] = n < 0 ? '-' : base_str[nbr % base];
	return (str);
}
