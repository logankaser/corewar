/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:39:38 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/04 12:59:08 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

// p3 - 1 or p3 ? How to access to register value ?

void	add(t_vm *vm, t_process *p, t_decode *d)
{
	int		p1;
	int		p2;
	int		p3;

	p1 = param_read(d, vm->arena, p, 0);
	p2 = param_read(d, vm->arena, p, 1);
	p3 = d->values[2];
	p->registers[p3 - 1] = p1 + p2;
	p->carry = p->registers[p3 - 1] ? 0 : 1;
}

void	sub(t_vm *vm, t_process *p, t_instruction_meta *im)
{
	int		p1;
	int		p2;
	int		p3;

	p1 = param_read(d, vm->arena, p, 0);
	p2 = param_read(d, vm->arena, p, 1);
	p3 = d->values[2];
	p->registers[p3 - 1] = p1 - p2;
	p->carry = p->registers[p3 - 1] ? 0 : 1;
}
