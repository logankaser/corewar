/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_dispatch.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:04:38 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/05 15:38:29 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"


void	no_op(t_vm *vm, t_process *p, t_decode *d)
{
	(void)vm;
	(void)p;
	(void)d;
}

t_instruction	*const g_instruction_dispatch[16] = {
	live,
	no_op,
	st,
	no_op,
	no_op,
	and,
	or,
	xor,
	no_op,
	ldi,
	sti,
	no_op,
	no_op,
	lldi,
	no_op,
	no_op,
};
