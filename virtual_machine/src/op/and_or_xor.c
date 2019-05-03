/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:02:59 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/03 15:07:35 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"

void    and(t_vm *vm, t_process *p, t_instruction_meta *im)
{
    int		p1;
	int		p2;
	int		p3;

	p1 = param_load(im, vm->arena, p->pc, 0);
	p2 = param_load(im, vm->arena, p->pc, 1);
	p3 = param_load(im, vm->arena, p->pc, 2);
	p->registers[p3 - 1] = (p->registers[p1 - 1] & p->registers[p2 - 1]);
    p->carry = p->registers[p3] ? 0 : 1;
    ft_printf("Good?");
}

void    or(t_vm *vm, t_process *p, t_instruction_meta *im)
{
    int		p1;
    int		p2;
    int		p3;

    p1 = param_load(im, vm->arena, p->pc, 0);
    p2 = param_load(im, vm->arena, p->pc, 1);
    p3 = param_load(im, vm->arena, p->pc, 2);
    p->registers[p3 - 1] = (p->registers[p1 - 1] | p->registers[p2 - 1]);
    p->carry = p->registers[p3] ? 0 : 1;
}

void    xor(t_vm *vm, t_process *p, t_instruction_meta *im)
{
    int		p1;
	int		p2;
	int		p3;

	p1 = param_load(im, vm->arena, p->pc, 0);
	p2 = param_load(im, vm->arena, p->pc, 1);
	p3 = param_load(im, vm->arena, p->pc, 2);
	p->registers[p3 - 1] = (p->registers[p1 - 1] ^ p->registers[p2 - 1]);
    p->carry = p->registers[p3] ? 0 : 1;
}
