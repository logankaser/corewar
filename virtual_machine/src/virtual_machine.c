/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:03:28 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/05 15:14:10 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "virtual_machine.h"
#include "instruction_dispatch.h"
#include "process.h"

void					vm_init(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->dump_cycle = UINT_MAX;
}

void					vm_del(t_vm *vm)
{
	unsigned	i;
	t_process	*proc;
	t_process	*tmp;

	i = 0;
	while (i < vm->player_count)
		free(vm->players[i++]);
	proc = vm->processes;
	while (proc)
	{
		tmp = proc;
		proc = proc->next;
		free(tmp);
	}
}

void					vm_run(t_vm *vm)
{
	t_process	*proc;
	t_decode	d;

	while (vm->processes)
	{
		vm->cycle += 1;
		if (vm->cycle >= vm->dump_cycle)
			break ;
		proc = vm->processes;
		while(proc)
		{
			if (vm->cycle < proc->execute_cycle)
			{
				// ft_printf("p: %p waiting %u cycles\n", proc, proc->execute_cycle - vm->cycle);
				proc = proc->next;
				continue ;
			}
			if (proc->executing != NONE)
			{
				uint8_t opi = proc->executing - 1;
				uint8_t enc = ARENA(vm, proc->pc + 1);
				ft_bzero(&d, sizeof(d));
				proc->step = decode(&d, &g_op_tab[opi], enc);
				bool loaded = decode_load(&d, &g_op_tab[opi], vm->arena, proc);
				if (loaded)
				{
					// ft_printf("p: %p executing op: \"%s\", param_size: %u, p1: %i, p2: %i, p3: %i\n",
					// 	proc,
					// 	g_op_tab[opi].name,
					// 	proc->step,
					// 	d.values[0],
					// 	d.values[1],
					// 	d.values[2]
					// );
					g_instruction_dispatch[opi](vm, proc, &d);
				}
				//else
				//	ft_printf("p: %p skipping op: \"%s\", bad params\n", proc, g_op_tab[opi].name);
				proc->pc += proc->step;
				proc->executing = NONE;
			}
			else
			{
				uint8_t op = ARENA(vm, proc->pc);
				if (op > 0 && op < 17)
				{
					//ft_printf("p: %p loading op: \"%s\"\n", proc, g_op_tab[op - 1].name);
					proc->executing = op;
					proc->execute_cycle = vm->cycle + (g_op_tab[op - 1].cycles - 1);
				}
				else
				{
					proc->pc += 1;
					proc->execute_cycle = vm->cycle + 1;
				}
			}
			proc = proc->next;
		}
		if (vm->cycle >= vm->check_cycle)
			process_check(vm, &vm->processes);
	}
}
