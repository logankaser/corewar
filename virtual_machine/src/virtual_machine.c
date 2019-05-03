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

void					vm_init(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->dump_cycle = UINT_MAX;
}

void					vm_del(t_vm *vm)
{
	unsigned i;

	i = 0;
	while (i < vm->player_count)
		free(vm->players[i++]);
}

void					vm_run(t_vm *vm)
{
	unsigned i;

	while (true)
	{
		vm->cycle += 1;
		if (vm->cycle >= vm->dump_cycle)
			break ;
		i = 0;
		while(i < vm->processes.length)
		{
			/*
			if (PROC(vm, i)->execute_cycle != vm->cycle)
				continue ;
			if (PROC(vm, i)->execute_cycle == vm->cycle)
			{
				unsigned offset = g_instruction_dispatch[PROC(vm, i)->executing - 1](vm->arena, PROC(vm, i));
				PROC(vm, i)->pc += offset;
				PROC(vm, i)->executing = ARENA(vm, PROC(vm, i)->pc);
				if (PROC(vm, i)->executing < 1 || PROC(vm, i)->executing > 16)
					PROC(vm, i)->executing = 0;
				else
					PROC(vm, i)->cycles_left = g_op_tab[PROC(vm, i)->executing - 1].cycles;
			}
			else
			{
				PROC(vm, i)->pc += 1;
				PROC(vm, i)->executing = ARENA(vm, PROC(vm, i)->pc);
			}
			*/
			uint8_t op = ARENA(vm, PROC(vm, i)->pc);
			uint8_t enc = ARENA(vm, PROC(vm, i)->pc + 1);
			if (op > 0 && op < 17 && validate_types(op, enc))
			{
				t_instruction_meta im;

				ft_bzero(&im, sizeof(im));
				decode(&im, op - 1, enc);
				ft_printf("Player %u:%s, op: %s, param_size: %u, p1: %i, p2: %i, p3: %i\n",
					PROC(vm, i)->player->number,
					PROC(vm, i)->player->header.prog_name,
					g_op_tab[op - 1].name,
					im.total_width,
					param_load(&im, vm->arena, PROC(vm, i)->pc, 0),
					param_load(&im, vm->arena, PROC(vm, i)->pc, 1),
					param_load(&im, vm->arena, PROC(vm, i)->pc, 2)
				);
				g_instruction_dispatch[op - 1](vm, PROC(vm, i), &im);
				PROC(vm, i)->pc += im.total_width;
			}
			else
				PROC(vm, i)->pc += 1;
			++i;
		}
	}
}
