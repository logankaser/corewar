/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:02:14 by lkaser            #+#    #+#             */
/*   Updated: 2019/03/15 19:02:15 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"

char	*ft_strf(const char *format, ...)
{
	t_uvector	s;
	va_list		args;

	if (format)
	{
		ft_uvector_init(&s, 1);
		va_start(args, format);
		format_iter(&s, (char*)format, args);
		va_end(args);
		return ((char*)s.data);
	}
	return (NULL);
}
