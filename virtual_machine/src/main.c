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
	ft_printf("Loaded warrrior: \"%s\":\n\tid: 0x%02x\n\tsize: %u\n"
		, player->header.prog_name, player->id,
		player->header.prog_size);
}

t_process *process_spawn(t_vm *vm, t_process *parent, unsigned pc)
{
	t_process *new_process;

	new_process = ft_memalloc(sizeof(t_process));
	if (parent)
	{
		ft_memcpy(new_process, parent, sizeof(t_process));
	}
	new_process->pc = pc;
	new_process->executing = NONE;
	new_process->execute_cycle = vm->cycle + 1;
	new_process->next = vm->processes;
	vm->processes = new_process;
	return (new_process);
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
		annouce_player(player);
		ft_memcpy(vm->arena + proc->pc,
			player->prog, player->header.prog_size);
		proc->registers[0] = 0 - (i + 1);
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
