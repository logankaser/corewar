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

void	ft_map_init(t_map *m, unsigned key_size, unsigned size)
{
	m->data = ft_memalloc(sizeof(t_bucket*) * size);
	m->count = 0;
	m->capacity = size;
	m->key_size = key_size;
}

/*
** Current implementation is chaining based.
*/

void	ft_map_set(t_map *m, const char *key, void *value)
{
	t_bucket	*bucket;
	uint32_t	hash;
	unsigned	index;

	hash = ft_map_hash_(m, key);
	index = hash % m->capacity;
	bucket = m->data[index];
	while (bucket && (bucket->hash != hash || ft_strcmp(bucket->key, key)))
		bucket = bucket->next;
	if (bucket)
		bucket->value = value;
	else
	{
		bucket = malloc(sizeof(t_bucket));
		*bucket = (t_bucket){.hash = hash, .value = value, .next = 0};
		if (m->key_size)
			bucket->key = ft_strsub(key, 0, m->key_size);
		else
			bucket->key = ft_strdup(key);
		bucket->next = m->data[index];
		m->data[index] = bucket;
	}
	m->count += 1;
	if (m->count / (double)m->capacity >= 0.7)
		ft_map_resize_(m, m->capacity * 2 + 1);
}

void	*ft_map_remove(t_map *m, const char *key)
{
	uint32_t	hash;
	t_bucket	*bucket;
	void		*value;
	t_bucket	*last;

	hash = ft_map_hash_(m, key);
	bucket = m->data[hash % m->capacity];
	last = NULL;
	while (bucket)
	{
		if (bucket->hash == hash && !ft_strcmp(bucket->key, key))
		{
			if (last)
				last->next = bucket->next;
			else
				m->data[hash % m->capacity] = bucket->next;
			value = bucket->value;
			free(bucket->key);
			free(bucket);
			return (value);
		}
		last = bucket;
		bucket = bucket->next;
	}
	return (NULL);
}

void	*ft_map_get(t_map *m, const char *key)
{
	uint32_t	hash;
	t_bucket	*bucket;

	hash = m->key_size ? ft_fnv_32((uint8_t*)key, m->key_size)
		: ft_fnv_32((uint8_t*)key, ft_strlen(key));
	bucket = m->data[hash % m->capacity];
	while (bucket)
	{
		if (bucket->hash == hash && !ft_strcmp(bucket->key, key))
			return (bucket->value);
		bucket = bucket->next;
	}
	return (NULL);
}

void	ft_map_clear(t_map *m, void (*free_fn)(void *))
{
	unsigned	i;
	t_bucket	*bucket;
	t_bucket	*tmp;

	i = 0;
	while (i < m->capacity)
	{
		if (!(bucket = m->data[i]))
		{
			++i;
			continue ;
		}
		while (bucket)
		{
			if (free_fn)
				free_fn(bucket->value);
			tmp = bucket;
			bucket = bucket->next;
			free(tmp->key);
			free(tmp);
		}
		m->data[i++] = NULL;
	}
	m->count = 0;
}
