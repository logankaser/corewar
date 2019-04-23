/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 18:14:20 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/23 09:05:56 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint32_t	ft_map_hash_(t_map *m, const char *key)
{
	uint32_t hash;

	if (m->key_size)
		hash = ft_fnv_32((const uint8_t*)key, m->key_size);
	else
		hash = ft_fnv_32((const uint8_t*)key, ft_strlen(key));
	return (hash);
}

void		ft_map_resize_(t_map *m, unsigned size)
{
	t_bucket	**new;
	unsigned	i;
	t_bucket	*bucket;
	t_bucket	*tmp;
	unsigned	index;

	new = ft_memalloc(sizeof(t_bucket*) * size);
	i = 0;
	while (i < m->capacity)
	{
		if (!(bucket = m->data[i++]))
			continue ;
		while (bucket)
		{
			tmp = bucket->next;
			index = bucket->hash % size;
			bucket->next = new[index];
			new[index] = bucket;
			bucket = tmp;
		}
	}
	free(m->data);
	m->data = new;
	m->capacity = size;
}
