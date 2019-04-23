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
#include <assert.h>
#include "libft.h"

void		ft_queue_init(t_queue *q, unsigned min_capacity)
{
	min_capacity -= 1;
	min_capacity |= min_capacity >> 1;
	min_capacity |= min_capacity >> 2;
	min_capacity |= min_capacity >> 4;
	min_capacity |= min_capacity >> 8;
	min_capacity |= min_capacity >> 16;
	q->tail = min_capacity;
	min_capacity += 1;
	q->capacity = min_capacity;
	q->length = 0;
	q->head = 0;
	q->data = ft_memalloc(sizeof(void*) * min_capacity);
}

static void	ft_queue_resize(t_queue *q, unsigned new_size)
{
	t_queue		new_q;

	assert(new_size > q->capacity);
	ft_queue_init(&new_q, new_size);
	while (q->length)
	{
		ft_queue_push(&new_q, ft_queue_pop(q));
	}
}

void		ft_queue_push(t_queue *q, void *d)
{
	if (q->length == q->capacity)
		ft_queue_resize(q, q->capacity * 2);
	q->tail = (q->tail + 1) & (q->capacity - 1);
	q->data[q->tail] = d;
	q->length += 1;
}

void		*ft_queue_pop(t_queue *q)
{
	void *tmp;

	if (q->length == 0)
		return (NULL);
	tmp = q->data[q->head];
	q->data[q->head] = NULL;
	q->head = (q->head + 1) & (q->capacity - 1);
	q->length -= 1;
	return (tmp);
}

void		*ft_queue_peek(t_queue *q)
{
	if (q->length == 0)
		return (NULL);
	return (q->data[q->head]);
}
