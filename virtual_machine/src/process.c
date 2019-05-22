/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:29:40 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/14 15:03:16 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

t_process	*process_spawn(t_vm *vm, t_process *parent, unsigned pc)
{
	static unsigned	id = 0;
	t_process		*new_process;

	new_process = ft_memalloc(sizeof(t_process));
	if (parent)
	{
		ft_memcpy(new_process, parent, sizeof(t_process));
	}
	new_process->pc = pc;
	new_process->executing = NONE;
	new_process->execute_cycle = vm->cycle + 1;
	new_process->next = vm->processes;
	new_process->id = ++id;
	vm->processes = new_process;
	return (new_process);
}

void		process_check(t_vm *vm, t_process **p)
{
	t_process	*tmp;

	while (*p)
	{
		if (vm->cycle - (*p)->last_live_cycle >= vm->cycles_to_die)
		{
			tmp = *p;
			*p = (*p)->next;
			free(tmp);
		}
		else
			p = &((*p)->next);
	}
	if (vm->lives >= NBR_LIVE || ++vm->checks >= MAX_CHECKS)
	{
		vm->checks = 0;
		if (vm->cycles_to_die > CYCLE_DELTA)
			vm->cycles_to_die = vm->cycles_to_die - CYCLE_DELTA;
		else
			vm->cycles_to_die = 0;
	}
	vm->lives = 0;
	vm->check_cycle = vm->cycle + vm->cycles_to_die;
}
