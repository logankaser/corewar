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

inline int32_t			param_load(t_instruction_meta *im, uint8_t *arena, unsigned pc, unsigned n)
{
	if (im->types[n] == REG)
		return (arena_load(arena, pc + im->offsets[n], 1));
	else if (im->types[n] == DIR)
		return (arena_load(arena, pc + im->offsets[n], im->direct_width));
	return (arena_load(arena, pc + im->offsets[n], 2));
}

static unsigned const	g_dir_size[2] = {
	4,
	2
};

void					decode(t_instruction_meta *im, uint8_t opi, uint8_t enc)
{
	unsigned	i;
	unsigned	offset;
	unsigned	size[4];

	im->direct_width = g_dir_size[g_op_tab[opi].halfwidth];
	size[0] = 0;
	size[REG] = 1;
	size[DIR] = im->direct_width;
	size[IND] = 2;
	if (!g_op_tab[opi].encoded)
	{
		im->offsets[0] = 1;
		im->types[0] = DIR;
		im->total_width = 1 + size[DIR];
		return;
	}
	i = 0;
	offset = 2;
	while(++i <= g_op_tab[opi].param_num)
	{
		im->offsets[i - 1] = offset;
		im->types[i - 1] = PX(enc, i);
		offset += size[im->types[i - 1]];
	}
	im->total_width = offset;
}
