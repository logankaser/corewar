/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:27:12 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:27:13 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ws(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *str)
{
	int		len;
	char	*trimmed;

	NULL_GUARD(str);
	while (*str && ws(*str))
		++str;
	len = ft_strlen(str);
	while (ws(str[len - 1]) && len > 0)
		--len;
	trimmed = (char *)malloc(len + 1);
	if (!trimmed)
		return (NULL);
	trimmed[len--] = '\0';
	while (len >= 0)
	{
		trimmed[len] = str[len];
		--len;
	}
	return (trimmed);
}
