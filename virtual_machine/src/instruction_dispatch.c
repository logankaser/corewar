/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_dispatch.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:04:38 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/26 14:04:40 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"

bool			no_op(uint8_t *a, t_process *p)
{
	(void)a;
	(void)p;
	return (false);
}

t_instruction	*g_instruction_dispatch[16] = {
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
};
