/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:02:59 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/04 17:50:03 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"

void	and(t_vm *vm, t_process *p, t_decode *d)
{
	int32_t	p1;
	int32_t	p2;

	p1 = param_read(d, vm->arena, p, 0);
	p2 = param_read(d, vm->arena, p, 1);
	if (d->values[2] == REG)
		p->registers[d->values[2] - 1] = p1 & p2;
	p->carry = p->registers[p3 - 1] ? 0 : 1;
	ft_printf("Good?");
}
void	or(t_vm *vm, t_process *p, t_decode *d)
{
	int32_t p1;
	int32_t p2;

	p1 = param_read(d, vm->arena, p, 0);
	p2 = param_read(d, vm->arena, p, 1);
	if (d->values[2] == REG)
		p->registers[d->values[2] - 1] = p1 | p2;
	p->carry = p->registers[p3 - 1] ? 0 : 1;
	ft_printf("Good?");
}
void	xor(t_vm *vm, t_process *p, t_decode *d)
{
	int32_t p1;
	int32_t p2;

	p1 = param_read(d, vm->arena, p, 0);
	p2 = param_read(d, vm->arena, p, 1);
	if (d->values[2] == REG)
		p->registers[d->values[2] - 1] = p1 ^ p2;
	p->carry = p->registers[p3 - 1] ? 0 : 1;
	ft_printf("Good?");
}
