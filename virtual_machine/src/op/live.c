/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 12:14:44 by tcherret          #+#    #+#             */
/*   Updated: 2019/05/21 13:21:38 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"

void	live(t_vm *vm, t_process *p, t_decode *d)
{
	int32_t		player_id;
	unsigned	i;

	p->last_live_cycle = vm->cycle;
	player_id = param_read(d, vm->arena, p, 0);
	if (player_id < 0 && player_id >= -4)
		p->owner = player_id;
	i = 0;
	while (i < vm->player_count)
	{
		if (vm->players[i]->id == player_id)
		{

			if (!vm->quiet && !vm->visual)
				ft_printf("Player %i (%s) is said to be alive\n",
					-player_id, vm->players[i]->header.prog_name);
			vm->players[i]->last_live_cycle = vm->cycle;
			break ;
		}
		i += 1;
	}
	vm->lives += 1;
}
