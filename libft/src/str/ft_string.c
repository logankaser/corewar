/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:25:31 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:25:34 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_string_append(t_uvector *v, const char *add)
{
	return (ft_string_appendn(v, add, ft_strlen(add)));
}

size_t		ft_string_appendn(t_uvector *v, const char *add, size_t size)
{
	char	null;
	size_t	len;

	if (size < 1)
		return (0);
	if (v->length > 0)
		ft_uvector_pop(v, NULL);
	null = '\0';
	len = 0;
	while (len++ < size)
		ft_uvector_push(v, add++);
	ft_uvector_push(v, &null);
	return (len);
}
