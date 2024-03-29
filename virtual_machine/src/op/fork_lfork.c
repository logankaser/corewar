/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 11:51:41 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/23 17:15:50 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"
#include "process.h"

void	ft_fork(t_vm *vm, t_process *p, t_decode *d)
{
	uint16_t index;

	index = d->values[0] % IDX_MOD;
	process_spawn(vm, p, (p->pc + index) % MEM_SIZE);
}

void	ft_lfork(t_vm *vm, t_process *p, t_decode *d)
{
	uint16_t index;

	index = d->values[0];
	process_spawn(vm, p, (p->pc + index) % MEM_SIZE);
}
