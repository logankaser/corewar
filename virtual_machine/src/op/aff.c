/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:46:04 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/04 12:50:55 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	aff(t_vm *vm, t_process *p, t_decode *d)
{
	int 			p1;
	char 			ascii;

	p1 = param_read(d, vm->arena, p, 0);
	ascii = p->registers[p1 - 1] % 256;
	write(1, &ascii, 1);
}
