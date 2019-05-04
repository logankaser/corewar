/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 12:14:44 by tcherret          #+#    #+#             */
/*   Updated: 2019/05/04 16:30:34 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"

void	st(t_vm *vm, t_process *p, t_decode *d)
{
	int32_t value;
	int32_t indirect;

	value = param_read(d, vm->arena, p, 0);
	if (d->types[1] == REG)
	{
		p->registers[d->values[1] - 1] = value; 
	}
	else if (d->types[1] == IND)
	{
		indirect = d->values[1];
		arena_store(vm->arena, p->pc + (indirect % IDX_MOD), value, REG_SIZE);
	}
}

void	sti(t_vm *vm, t_process *p, t_decode *d)
{
	int32_t value;
	int32_t index;

	value = param_read(d, vm->arena, p, 0);
	index = 0;
	if (d->types[1] == IND)
		index = d->values[1];
	else
		index = param_read(d, vm->arena, p, 1);
	index += param_read(d, vm->arena, p, 2);
	arena_store(vm->arena, p->pc + index, value, REG_SIZE);
}
