/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:51:53 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/06 15:28:40 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
#include "decode.h"

void	zjmp(t_vm *vm, t_process *p, t_decode *d)
{
	int16_t	p1;

	p1 = param_read(d, vm->arena, p, 0);
	if (p->carry == 1)
		p->step = p1;
}
