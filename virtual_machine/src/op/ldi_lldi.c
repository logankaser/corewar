/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 12:14:44 by tcherret          #+#    #+#             */
/*   Updated: 2019/04/28 12:40:23 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"

void	ldi(t_vm *vm, t_process *p, t_decode *d)
{
	int32_t	offset;
	int32_t	value;

	offset = param_read(d, vm->arena, p, 0) + param_read(d, vm->arena, p, 1);
	value = arena_load(vm->arena, p->pc + (offset % IDX_MOD), d->direct_width);
	p->registers[d->values[2]] = value;
	p->carry = !value;
}

void	lldi(t_vm *vm, t_process *p, t_decode *d)
{
	int32_t	offset;
	int32_t	value;

	offset = param_read(d, vm->arena, p, 0) + param_read(d, vm->arena, p, 1);
	value = arena_load(vm->arena, p->pc + offset, d->direct_width);
	p->registers[d->values[2]] = value;
	p->carry = !value;
}
