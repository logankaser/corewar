/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:26:08 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:26:10 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *str, char (*fn)(unsigned, char))
{
	char		*new;
	unsigned	i;

	NULL_GUARD((str && fn));
	i = ft_strlen(str);
	new = malloc(i + 1);
	if (!new)
		return (NULL);
	new[i] = '\0';
	i = 0;
	while (*str)
	{
		new[i] = fn(i, *str);
		++i;
		++str;
	}
	return (new);
}
