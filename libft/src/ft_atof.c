/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:21:03 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/17 11:40:48 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"

double	ft_atof(const char *str)
{
	bool		neg;
	bool		point;
	unsigned	fac;
	double		out;

	out = 0.0;
	fac = 1;
	point = false;
	if (!ft_strcmp("nan", str))
		return (NAN);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		++str;
	if ((neg = *str == '-') || *str == '+')
		++str;
	while ((*str >= '0' && *str <= '9') || (*str == '.' && !point))
	{
		if (point)
			fac *= 10;
		if (*str == '.')
			point = true;
		else
			out = out * 10.0f + (double)(*str - '0');
		++str;
	}
	return ((neg ? -out : out) / fac);
}
