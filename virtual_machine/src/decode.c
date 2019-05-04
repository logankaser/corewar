/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:06:34 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/01 17:06:35 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "libft.h"
#include "op.h"
#include "decode.h"

inline int32_t			arena_load(uint8_t *arena, unsigned from, unsigned size)
{
	int32_t	out;

	assert(size == 1 || size == 2 || size == 4);
	if (size == 1)
		return (arena[from % MEM_SIZE]);
	else if (size == 2)
	{
		((uint8_t*)&out)[1] = arena[from % MEM_SIZE];
		((uint8_t*)&out)[0] = arena[(from + 1) % MEM_SIZE];
		return ((int16_t)out);
	}
	((uint8_t*)&out)[3] = arena[from % MEM_SIZE];
	((uint8_t*)&out)[2] = arena[(from + 1) % MEM_SIZE];
	((uint8_t*)&out)[1] = arena[(from + 2) % MEM_SIZE];
	((uint8_t*)&out)[0] = arena[(from + 3) % MEM_SIZE];
	return (out);
}

static unsigned const	g_dir_size[2] = {
	4,
	2
};

unsigned				decode(t_decode *d, const t_op *op, uint8_t enc)
{
	unsigned	i;
	unsigned	offset;
	unsigned	size[4];

	size[0] = 0;
	size[REG] = 1;
	size[DIR] = g_dir_size[op->halfwidth];
	size[IND] = 2;
	if (!op->encoded)
	{
		d->offsets[0] = 1;
		d->types[0] = DIR;
		return 1 + size[DIR];
	}
	i = 0;
	offset = 2;
	while(i < op->param_num)
	{
		d->offsets[i] = offset;
		d->types[i] = PX(enc, i + 1);
		offset += size[d->types[i]];
		i += 1;
	}
	return offset;
}

static uint8_t const	g_type[4] = {
	0,
	T_REG,
	T_DIR,
	T_IND
};

bool					load_params(t_decode *d, const t_op *op, uint8_t *arena, t_process *p)
{
	unsigned i;

	i = 0;
	while (i < op->param_num)
	{
		if (!(g_type[d->types[i]] & op->param_types[i]))
			return (false);
		if (d->types[i] == REG)
		{
			d->values[i] = arena_load(arena, p->pc + d->offsets[i] , 1);
			if ((uint8_t)d->values[i] >= REG_NUMBER)
				return (false);
			d->values[i] = p->registers[(uint8_t)d->values[i]];
		}
		else if (d->types[i] == DIR)	
			d->values[i] = arena_load(arena, p->pc + d->offsets[i],
				g_dir_size[op->halfwidth]);
		else if (d->types[i] == IND)
		{
			d->values[i] = arena_load(arena, p->pc + d->offsets[i], 2);
			d->values[i] = arena_load(arena, p->pc + (d->values[i] % IDX_MOD),
				g_dir_size[op->halfwidth]);
		}
		i += 1;
	}
	return (true);
}

