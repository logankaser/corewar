/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 12:14:44 by tcherret          #+#    #+#             */
/*   Updated: 2019/05/04 16:30:49 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"

void	live(t_vm *vm, t_process *p, t_decode *d)
{
	int32_t		player_id;
	unsigned	i;

	p->last_live_cycle = vm->cycle;
	player_id = param_read(d, vm->arena, p, 0);
	i = 0;
	while (i < vm->player_count)
	{
		if (vm->players[i]->id == player_id)
		{
			if (!vm->quiet)
				ft_printf("A process shows that player %i (%s) is alive\n",
					-player_id, vm->players[i]->header.prog_name);
			vm->players[i]->last_live_cycle = vm->cycle;
			break ;
		}
		i += 1;
	}
	vm->lives += 1;
}
