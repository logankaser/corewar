/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_dispatch.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:04:38 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/06 15:37:09 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"

void			no_op(t_vm *vm, t_process *p, t_decode *d)
{
	(void)vm;
	(void)p;
	(void)d;
}

t_instruction	*const g_instruction_dispatch[16] = {
	live,
	ld,
	st,
	add,
	sub,
	and,
	or,
	xor,
	zjmp,
	ldi,
	sti,
	ft_fork,
	lld,
	lldi,
	ft_lfork,
	aff,
};
