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
	while (true)
	{
		vm->cycle += 1;
		if (vm->cycle >= vm->dump_cycle)
			break ;
		for (unsigned i = 0; i < vm->processes.length; ++i)
		{
			ft_printf("Player %s:\n\tcurrent op: 0x%02hhx\n",
				PROC(vm, i)->player->header.prog_name,
				ARENA(vm, PROC(vm, i)->pc));
		}
	}
}
