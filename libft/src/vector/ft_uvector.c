/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvector.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:27:33 by lkaser            #+#    #+#             */
/*   Updated: 2018/08/31 09:42:05 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void				ft_uvector_init(t_uvector *v, unsigned size)
{
	v->width = size;
	v->data = malloc(size * 8);
	v->capacity = 8;
	v->length = 0;
}

void				ft_uvector_resize(t_uvector *v, unsigned size)
{
	uint8_t		*new;

	if (size > v->length)
	{
		new = realloc(v->data, size * v->width);
		v->data = new;
		v->capacity = size;
	}
}

void				ft_uvector_push(t_uvector *v, const void *d)
{
	if (v->length < v->capacity)
		ft_memcpy(v->data + v->width * v->length++, d, v->width);
	else
	{
		ft_uvector_resize(v, v->capacity * 2);
		ft_uvector_push(v, d);
	}
}

void				*ft_uvector_pop(t_uvector *v, void *item)
{
	if (v->length == 0)
		return (NULL);
	if (!item)
	{
		--v->length;
		return (NULL);
	}
	ft_memcpy(item, v->data + v->width * --v->length, v->width);
	return (item);
}

void				*ft_uvector_get(t_uvector *v, unsigned i)
{
	if (!v->length || i > v->length - 1)
		return (NULL);
	return (v->data + v->width * i);
}
