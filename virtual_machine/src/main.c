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
	ft_printf(
		"* Player %i, weighing %u bytes, \"%s\" (\"%s\") !\n",
		-player->id,
		player->header.prog_size,
		player->header.prog_name,
		player->header.comment,
		player->id
	);
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
	vm->check_cycle = vm->cycles_to_die;
}

static void	annouce_winner(t_vm *vm)
{
	unsigned	i;
	unsigned	most_recent_live;
	t_player	*player;

	i = 0;
	most_recent_live = 0;
	player = NULL;
	while (i < vm->player_count)
	{
		if (vm->players[i]->last_live_cycle >= most_recent_live)
		{
			most_recent_live = vm->players[i]->last_live_cycle;
			player = vm->players[i];
		}
		i += 1;
	}
	if (player && player->last_live_cycle > 0)
		ft_printf("Contestant %i, \"%s\", has won !\n",
			-player->id, player->header.prog_name, player->header.comment);
	else
		ft_printf("No winner, no one called live!\n");
}


int			main(int argc, char **argv)
{
	t_vm vm;

	vm_init(&vm);
	parse_options(argc, argv, &vm);
	if (vm.player_count == 0)
	{
		ft_fprintf(stderr, "corewar: no players!\n");
		exit_usage(&vm);
	}
	ft_putendl("Introducing contestants...");
	start_players(&vm);
	vm_run(&vm);
	annouce_winner(&vm);
	ft_printf("final cycle: %u\n", vm.cycle);
	vm_del(&vm);
}
