/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:26:04 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:26:05 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *str, char (*fn)(char))
{
	char		*new;
	unsigned	i;

	NULL_GUARD((str && fn));
	i = ft_strlen(str);
	new = malloc(i + 1);
	NULL_GUARD(new);
	new[i] = '\0';
	i = 0;
	while (*str)
		new[i++] = fn(*str++);
	return (new);
}
