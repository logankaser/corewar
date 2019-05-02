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

/*
** Validate encoding byte types, if any parameters
** are not valid types in that postion return false
** extra bits after the valid number of parameters are
** ignored;
** This works because param_types[n] is always 0 if n
** is greater than param_num.
*/

static uint8_t const	g_type[4] = {
	0,
	T_REG,
	T_DIR,
	T_IND
};

bool					validate_types(uint8_t opi, uint8_t enc)
{
	unsigned valid_count;

	opi -= 1;
	if (!g_op_tab[opi].encoded)
		return (true);
	valid_count = 0;
	if (g_type[P1(enc)] & g_op_tab[opi].param_types[0])
		valid_count += 1;
	if (g_type[P2(enc)] & g_op_tab[opi].param_types[1])
		valid_count += 1;
	if (g_type[P3(enc)] & g_op_tab[opi].param_types[2])
		valid_count += 1;
	return (g_op_tab[opi].param_num == valid_count);
}

/*
** Get size of params including the type encoding byte if present for that op,
** respecting halfwidth (direct 2 bytes) and only counting up to
** param_num parameters.
*/

static unsigned const	g_dir_size[2] = {
	4,
	2
};

unsigned				encoded_size(uint8_t opi, uint8_t enc)
{
	unsigned	size[4];

	opi -= 1;
	size[0] = 0;
	size[REG] = 1;
	size[DIR] = g_dir_size[g_op_tab[opi].halfwidth];
	size[IND] = 2;
	if (!g_op_tab[opi].encoded)
		return (1 + size[DIR]);
	if (g_op_tab[opi].param_num == 1)
		return (2 + size[P1(enc)]);
	else if (g_op_tab[opi].param_num == 2)
		return (2 + size[P1(enc)] + size[P2(enc)]);
	return (2 + size[P1(enc)] + size[P2(enc)] + size[P3(enc)]);
}

static int32_t			load(uint8_t *arena, unsigned from, unsigned size)
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

/*
** Returns the parameter specified,
** indirects return the value the indirect points at for convience 
*/

void				load_params(t_params params, uint8_t *arena, unsigned pc)
{
	uint8_t 	opi;
	uint8_t 	enc;
	unsigned	i;
	unsigned	offset;
	unsigned	size[4];

	opi = arena[pc % MEM_SIZE] - 1;
	if (g_op_tab[opi].encoded)
	{
		enc = arena[(pc + 1) % MEM_SIZE];
		size[0] = 0;
		size[REG] = 1;
		size[DIR] = g_dir_size[g_op_tab[opi].halfwidth];
		size[IND] = 2;
		i = 0;
		offset = 2;
		while(++i <= g_op_tab[opi].param_num)
		{
			params[i - 1] = load(arena, pc + offset, size[PX(enc, i)]);
			if (PX(enc, i) == IND)
			{
				ft_printf("%u\n");
				unsigned index = (pc + params[i - 1]) % MEM_SIZE;
				params[i - 1] = load(arena, pc + params[i - 1], size[DIR]);
			}
			offset += size[PX(enc, i)];
		}
	}
	params[0] = (int16_t)load(arena, pc + 1, 2);
}
