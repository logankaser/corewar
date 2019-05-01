/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:03:28 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/27 18:48:41 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "virtual_machine.h"
#include "instruction_dispatch.h"

/*
** Validate encoding byte types, if any parameters
** are not valid types in that postion return false
** extra bits after the valid number of parameters are
** ignored;
** This works because param_types[n] is always 0 if n
** is greater than param_num.
*/

static uint8_t g_type[4] = {
	0,
	T_REG,
	T_DIR,
	T_IND
};

bool		validate_types(uint8_t *arena, unsigned pc)
{
	uint8_t opi;
	uint8_t enc;
	uint8_t valid_count;

	opi = arena[pc % MEM_SIZE] - 1;
	if (!g_op_tab[opi].encoded)
		return (true);
	enc = arena[(pc + 1) % MEM_SIZE];
	valid_count = 0;
	if (g_type[P1(enc)] & g_op_tab[opi].param_types[0])
		valid_count += 1;
	if (g_type[P2(enc)] & g_op_tab[opi].param_types[1])
		valid_count += 1;
	if (g_type[P3(enc)] & g_op_tab[opi].param_types[2])
		valid_count += 1;
	return g_op_tab[opi].param_num == valid_count;
}

/*
** Get size of params including the type encoding byte if present for that op,
** respecting halfwidth (direct 2 bytes) and only counting up to
** param_num parameters. 
*/

unsigned	encoded_size(uint8_t *arena, unsigned pc)
{
	uint8_t		opi;
	uint8_t		enc;
	uint8_t		size[4];


	opi = arena[pc % MEM_SIZE] - 1;
	size[0] = 0;
	size[REG] = 1;
	size[DIR] = DIR_SIZE - (g_op_tab[opi].halfwidth * 2);
	size[IND] = 2;
	if (!g_op_tab[opi].encoded)
		return 1 + size[DIR];
	enc = arena[(pc + 1) % MEM_SIZE];
	if (g_op_tab[opi].param_num == 1)
		return 2 + size[P1(enc)];
	else if (g_op_tab[opi].param_num == 2)
		return 2 + size[P1(enc)] + size[P2(enc)];
	return 2 + size[P1(enc)] + size[P2(enc)] + size[P3(enc)];
}

void	vm_init(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->dump_cycle = UINT_MAX;
}

void	vm_del(t_vm *vm)
{
	unsigned i;

	i = 0;
	while (i < vm->player_count)
		free(vm->players[i++]);
}

void	vm_run(t_vm *vm)
{
	uint8_t m;

	while (true)
	{
		vm->cycle += 1;
		if (vm->cycle >= vm->dump_cycle)
			break ;
		for (unsigned i = 0; i < vm->processes.length; ++i)
		{
			// if (PROC(vm, i)->execute_cycle != vm->cycle)
			// 	continue ;
			// if (PROC(vm, i)->execute_cycle == vm->cycle)
			// {
			// 	unsigned offset = g_instruction_dispatch[PROC(vm, i)->executing - 1](vm->arena, PROC(vm, i));
			// 	PROC(vm, i)->pc += offset;
			// 	PROC(vm, i)->executing = ARENA(vm, PROC(vm, i)->pc);
			// 	if (PROC(vm, i)->executing < 1 || PROC(vm, i)->executing > 16)
			// 		PROC(vm, i)->executing = 0;
			// 	else
			// 		PROC(vm, i)->cycles_left = g_op_tab[PROC(vm, i)->executing - 1].cycles;
			// }
			// else
			// {
			// 	PROC(vm, i)->pc += 1;
			// 	PROC(vm, i)->executing = ARENA(vm, PROC(vm, i)->pc);
			// }
			m = ARENA(vm, PROC(vm, i)->pc);
			if (m > 0 && m < 17 && validate_types(vm->arena, PROC(vm, i)->pc))
			{
				ft_printf("Player %u:%s, op: %s, param_size: %u\n",
				PROC(vm, i)->player->number,
				PROC(vm, i)->player->header.prog_name,
				g_op_tab[m - 1].name,
				encoded_size(vm->arena, PROC(vm, i)->pc));
			}
			PROC(vm, i)->pc += 1;
		}
	}
}
