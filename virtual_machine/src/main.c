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
#include "process.h"
#include "virtual_machine.h"
#include "instruction_dispatch.h"

static void	annouce_player(t_player *player)
{
	ft_printf("Loaded warrrior: \"%s\":\n\tid: 0x%02x\n\tsize: %u\n"
		, player->header.prog_name, player->id,
		player->header.prog_size);
}

static void	start_players(t_vm *vm)
{
	int			i;
	t_player	*player;
	t_process	*proc;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		player = vm->players[i];
		if (!player)
			continue;
		proc = process_spawn(vm, NULL,
			(MEM_SIZE / vm->player_count) * i);
		player->id = -player->id;
		proc->registers[0] = player->id;
		annouce_player(player);
		ft_memcpy(vm->arena + proc->pc,
			player->prog, player->header.prog_size);
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
