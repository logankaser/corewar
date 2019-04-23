/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:25:37 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:25:40 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *str, void (*fn)(char *))
{
	if (str && fn)
		while (*str)
			fn(str++);
}

void	ft_striter_u(char *str, int (*fn)(int))
{
	if (str && fn)
		while (*str)
		{
			*str = fn(*str);
			++str;
		}
}
