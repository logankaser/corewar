/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:25:05 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:25:09 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *a, const char *b)
{
	while (*a || *b)
	{
		if (*a != *b)
			return (*(unsigned char *)a - *(unsigned char *)b);
		++a;
		++b;
	}
	return (0);
}
