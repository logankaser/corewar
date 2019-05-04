/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:02:59 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/03 17:04:39 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"

//FIXME: add, or, xor

void    and(t_vm *vm, t_process *p, t_instruction_meta *im)
{
    int		p1;
	int		p2;
	int		p3;

	p1 = param_load(im, vm->arena, p->pc, 0);
	p2 = param_load(im, vm->arena, p->pc, 1);
	p3 = param_load(im, vm->arena, p->pc, 2);
    if (VALID_REG(p3) && im->types[0] == REG && VALID_REG(p1) && /
        im->types[1] == REG && VALID_REG(p2))
    {
        if (im->types[0] == IND)
            p1 = arena_load(vm->arena, (p->pc + p1) % IDX_MOD, REG_SIZE);
        else if (im->types[0] == REG && VALID_REG(p1))
            p1 = p->registers[p1 - 1];
        if (im->types[1] == IND)
            p2 = arena_load(vm->arena, (p->pc + p2) % IDX_MOD, REG_SIZE);
        else if (im->types[1] == REG && VALID_REG(p2))
            p2 = p->registers[p2 - 1];
        p->registers[p3 - 1] = (p1 & p2);
        p->carry = p->registers[p3 - 1] ? 0 : 1;
    }
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
    if (VALID_REG(p3) && im->types[0] == REG && VALID_REG(p1) && /
        im->types[1] == REG && VALID_REG(p2))
    {
        if (im->types[0] == IND)
            p1 = arena_load(vm->arena, (p->pc + p1) % IDX_MOD, REG_SIZE);
        else if (im->types[0] == REG && VALID_REG(p1))
            p1 = p->registers[p1 - 1];
        if (im->types[1] == IND)
            p2 = arena_load(vm->arena, (p->pc + p2) % IDX_MOD, REG_SIZE);
        else if (im->types[1] == REG && VALID_REG(p2))
            p2 = p->registers[p2 - 1];
        p->registers[p3 - 1] = (p1 | p2);
        p->carry = p->registers[p3 - 1] ? 0 : 1;
    }
    ft_printf("Good?");
}

void    xor(t_vm *vm, t_process *p, t_instruction_meta *im)
{
    int		p1;
	int		p2;
	int		p3;

	p1 = param_load(im, vm->arena, p->pc, 0);
	p2 = param_load(im, vm->arena, p->pc, 1);
	p3 = param_load(im, vm->arena, p->pc, 2);
    if (VALID_REG(p3) && im->types[0] == REG && VALID_REG(p1) && /
        im->types[1] == REG && VALID_REG(p2))
    {
        if (im->types[0] == IND)
            p1 = arena_load(vm->arena, (p->pc + p1) % IDX_MOD, REG_SIZE);
        else if (im->types[0] == REG && VALID_REG(p1))
            p1 = p->registers[p1 - 1];
        if (im->types[1] == IND)
            p2 = arena_load(vm->arena, (p->pc + p2) % IDX_MOD, REG_SIZE);
        else if (im->types[1] == REG && VALID_REG(p2))
            p2 = p->registers[p2 - 1];
        p->registers[p3 - 1] = (p1 ^ p2);
        p->carry = p->registers[p3 - 1] ? 0 : 1;
    }
    ft_printf("Good?");
}
