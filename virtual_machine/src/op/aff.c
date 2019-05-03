/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:46:04 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/03 15:30:02 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	aff(t_vm *vm, t_process *p, t_instruction_meta *im)
{
	int 			p1;
	char 			ascii;


	p1 = param_load(im, vm->arena, p->pc, 0);
	if (VALID_REG(p1))
	{
		ascii = p->registers[p1 - 1] % 256;
		write(1, &ascii, 1);
	}
}
