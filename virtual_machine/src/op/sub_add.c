/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:39:38 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/03 15:31:03 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	add(t_vm *vm, t_process *p, t_instruction_meta *im)
{
	int		p1;
	int		p2;
	int		p3;

	p1 = param_load(im, vm->arena, p->pc, 0);
	p2 = param_load(im, vm->arena, p->pc, 1);
	p3 = param_load(im, vm->arena, p->pc, 2);
	if (VALID_REG(p1) && VALID_REG(p2) && VALID_REG(p3))
	{
		p->registers[p3 - 1] = p->registers[p1 - 1] + p->registers[p2 - 1];
		p->carry = p->registers[p3] ? 0 : 1;
	}
}

void	sub(t_vm *vm, t_process *p, t_instruction_meta *im)
{
	int		p1;
	int		p2;
	int		p3;

	p1 = param_load(im, vm->arena, p->pc, 0);
	p2 = param_load(im, vm->arena, p->pc, 1);
	p3 = param_load(im, vm->arena, p->pc, 2);
	if (VALID_REG(p1) && VALID_REG(p2) && VALID_REG(p3))
	{
		p->registers[p3 - 1] = p->registers[p1 - 1] - p->registers[p2 - 1];
		p->carry = p->registers[p3] ? 0 : 1;
	}
}
