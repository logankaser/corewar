/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:25:22 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:25:23 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*copy;
	size_t	size;

	size = ft_strlen(str) + 1;
	NULL_GUARD(copy = malloc(size));
	ft_memcpy(copy, str, size);
	return (copy);
}
