/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:27:33 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/08 15:23:03 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_vector_init(t_vector *v)
{
	v->data = malloc(sizeof(void*) * 8);
	v->capacity = 8;
	v->length = 0;
}

void				ft_vector_resize(t_vector *v, unsigned size)
{
	void		**new;
	unsigned	i;

	if (size > v->length)
	{
		new = malloc(sizeof(void*) * size);
		i = 0;
		while (i < v->length)
		{
			new[i] = v->data[i];
			++i;
		}
		free(v->data);
		v->data = new;
		v->capacity = size;
	}
}

void				ft_vector_push(t_vector *v, void *d)
{
	if (v->length < v->capacity)
		v->data[v->length++] = d;
	else
	{
		ft_vector_resize(v, v->capacity * 2);
		ft_vector_push(v, d);
	}
}

void				*ft_vector_pop(t_vector *v)
{
	void **item;

	item = NULL;
	if (v->length > 0)
		item = v->data[--v->length];
	return (item);
}

void				ft_vector_del(t_vector *v)
{
	unsigned	i;

	i = 0;
	while (i < v->length)
		free(v->data[i++]);
	free(v->data);
	*v = (t_vector){0, 0, 0};
}
