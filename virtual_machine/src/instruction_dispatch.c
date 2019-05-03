/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_dispatch.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:04:38 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/03 15:14:39 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"


void	no_op(t_vm *vm, t_process *p, t_instruction_meta *im)
{
	(void)vm;
	(void)p;
	(void)im;
}

t_instruction	*const g_instruction_dispatch[16] = {
	live,
	no_op,
	no_op,
	add,
	sub,
	and,
	or,
	xor,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
};
