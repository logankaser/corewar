/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:51:53 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/03 15:44:33 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"

void    zjmp(t_vm *vm, t_process *p, t_instruction_meta *im)
{
	int16_t p1;

	p1 = param_load(im, vm->arena, p->pc, 0);
    if (vm && p->carry == 1)
		p->step = p1 % IDX_MOD; // is this like that, or we also move the size of the instruction + p->step?
}
