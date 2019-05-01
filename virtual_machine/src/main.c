/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:28:10 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/23 14:23:42 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "virtual_machine.h"
#include "instruction_dispatch.h"

static void	annouce_player(t_player *player)
{
	ft_printf("Loaded warrrior: \"%s\":\n\tdesc: \"%s\"\n\tsize: %u\n"
		, player->header.prog_name, player->header.comment,
		player->header.prog_size);
}

static void	start_players(t_vm *vm)
{
	int			i;
	t_player	*player;
	t_process	*proc;

	ft_vector_init(&vm->processes);
	i = MAX_PLAYERS;
	while (--i >= 0)
	{
		player = vm->players[i];
		if (!player)
			continue;
		annouce_player(player);
		proc = ft_memalloc(sizeof(t_process));
		proc->pc =
			(sizeof(vm->arena) / vm->player_count) * (player->number - 1);
		ft_memcpy(vm->arena + proc->pc,
			player->prog, player->header.prog_size);
		proc->executing = ARENA(vm, proc->pc);
		proc->player = player;
		proc->registers[0] = 0 - (i + 1);
		proc->execute_cycle = vm->cycle + 1;
		ft_vector_push(&vm->processes, proc);
	}
}

int			main(int argc, char **argv)
{
	t_vm vm;

	vm_init(&vm);
	parse_options(argc, argv, &vm);
	start_players(&vm);
	vm_run(&vm);
	vm_del(&vm);
}
