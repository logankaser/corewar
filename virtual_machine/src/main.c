/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:28:10 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/23 17:16:35 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "process.h"
#include "virtual_machine.h"
#include "instruction_dispatch.h"
#include "visual.h"

static void	annouce_player(t_player *player)
{
	ft_printf(
		"* Player %i, weighing %u bytes, \"%s\" (\"%s\") !\n",
		-player->id,
		player->header.prog_size,
		player->header.prog_name,
		player->header.comment,
		player->id);
}

static void	start_players(t_vm *vm)
{
	int			i;
	t_player	*player;
	t_process	*proc;

	i = -1;
	if (vm->dump_cycle == UINT_MAX)
		ft_putendl("Introducing contestants...");
	while (++i < MAX_PLAYERS)
	{
		player = vm->players[i];
		if (!player)
			continue;
		proc = process_spawn(vm, NULL,
			(MEM_SIZE / vm->player_count) * i);
		player->id = -player->id;
		proc->registers[0] = player->id;
		proc->owner = player->id;
		if (vm->dump_cycle == UINT_MAX)
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

static void	dump_memory(t_vm *vm)
{
	unsigned i;

	i = 1;
	while (i <= MEM_SIZE)
	{
		ft_printf("%02hhx ", vm->arena[i - 1]);
		if (i % 32 == 0)
			ft_putchar('\n');
		i += 1;
	}
	vm_del(vm);
	exit(0);
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
	start_players(&vm);
	if (vm.visual)
		init_visual();
	vm_run(&vm);
	if (vm.visual)
	{
		vm.pause = true;
		render(&vm);
		endwin();
	}
	if (vm.dump_cycle != UINT_MAX)
		dump_memory(&vm);
	annouce_winner(&vm);
	if (!vm.quiet)
		ft_printf("final cycle: %u\n", vm.cycle);
	vm_del(&vm);
	return 0;
}
