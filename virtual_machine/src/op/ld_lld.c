/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 19:18:59 by tcherret          #+#    #+#             */
/*   Updated: 2019/05/04 13:04:56 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	ld(t_vm *vm, t_process *p, t_decode *d)
{
	int	p1;
	int	p2;

	p1 = param_read(d, vm->arena, p, 0);
	p2 = d->values[1];
	p->registers[p2 - 1] = p1;
	p->carry = p->registers[p2 - 1] ? 0 : 1;
}

void	lld(t_vm *vm, t_process *p, t_instruction_meta *im)
{
	int	p1;
	int	p2;

	p1 = d->values[0];
	p2 = d->values[1];
	if (im->types[0] == DIR)
		p->registers[p2 - 1] = p1;
	else if (im->types[0] == IND)
	{
		p1 = arena_load(vm->arena, (p->pc + p1), REG_SIZE);
		p->registers[p2 - 1] = p1;
	}
	p->carry = p->registers[p2 - 1] ? 0 : 1;
}
