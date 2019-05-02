/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 12:14:44 by tcherret          #+#    #+#             */
/*   Updated: 2019/04/28 12:40:23 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	live(t_vm *vm, t_process *p, t_instruction_meta *im)
{
	int32_t player;

	p->last_live_cycle = vm->cycle;
	player = param_load(im, vm->arena, p->pc, 0);
	if (player > 0 && player <= MAX_PLAYERS && vm->players[player - 1])
	{
		ft_printf("A process shows that player %i (%s) is alive\n",
			player, vm->players[player - 1]->header.prog_name);
		vm->players[player - 1]->last_live_cycle = vm->cycle;
	}
	p->player->last_live_cycle = vm->cycle;
}
