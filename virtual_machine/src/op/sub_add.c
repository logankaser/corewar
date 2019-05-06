/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:39:38 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/06 15:27:42 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
#include "decode.h"

void	add(t_vm *vm, t_process *p, t_decode *d)
{
	int32_t		p1;
	int32_t		p2;
	int32_t		p3;

	p1 = param_read(d, vm->arena, p, 0);
	p2 = param_read(d, vm->arena, p, 1);
	p3 = d->values[2];
	p->registers[p3 - 1] = p1 + p2;
	p->carry = p->registers[p3 - 1] ? 0 : 1;
}

void	sub(t_vm *vm, t_process *p, t_decode *d)
{
	int32_t		p1;
	int32_t		p2;
	int32_t		p3;

	p1 = param_read(d, vm->arena, p, 0);
	p2 = param_read(d, vm->arena, p, 1);
	p3 = d->values[2];
	p->registers[p3 - 1] = p1 - p2;
	p->carry = p->registers[p3 - 1] ? 0 : 1;
}
