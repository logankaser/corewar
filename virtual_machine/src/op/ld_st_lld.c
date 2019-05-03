/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 19:18:59 by tcherret          #+#    #+#             */
/*   Updated: 2019/05/03 15:32:01 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	ld(t_vm *vm, t_process *p, t_instruction_meta *im)
{
	int	p1;
	int	p2;

	p1 = param_load(im, vm->arena, p->pc, 0);
	p2 = param_load(im, vm->arena, p->pc, 1);
	if (VALID_REG(p2))
	{
		if (im->types[0] == DIR)
			p->registers[p2 - 1] = p1;
		else if (im->types[0] == IND)
		{
			p1 = arena_load(vm->arena, (p->pc + p1) % IDX_MOD, REG_SIZE);
			p->registers[p2 - 1] = p1;
		}
		p->carry = p->registers[p2 - 1] ? 0 : 1;
	}
}

/*void	st(t_vm *vm, t_process *p, t_instruction_meta *im)
  {
  int	p1;
  int	p2;

  p1 = param_load(im, vm->arena, p->pc, 0);
  p2 = param_load(im, vm->arena, p->pc, 1);
  if (type[1] == REG)
  p->registers[p2 - 1] = p->registers[p1 - 1];
  else if (type[1] == IND)
  {
  }
  }*/

void	lld(t_vm *vm, t_process *p, t_instruction_meta *im)
{
	int	p1;
	int	p2;

	p1 = param_load(im, vm->arena, p->pc, 0);
	p2 = param_load(im, vm->arena, p->pc, 1);
	if (VALID_REG(p2))
	{
		if (im->types[0] == DIR)
			p->registers[p2 - 1] = p1;
		else if (im->types[0] == IND)
		{
			p1 = arena_load(vm->arena, (p->pc + p1), REG_SIZE);
			p->registers[p2 - 1] = p1;
		}
		p->carry = p->registers[p2 - 1] ? 0 : 1;
	}
}
