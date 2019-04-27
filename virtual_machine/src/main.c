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
	ft_printf("Loaded warrrior: \"%s\"\n\tdesc: \"%s\"\n\tsize: %u"
		, player->header.prog_name, player->header.comment,
		player->header.prog_size);
}

/*
** FIXME: Players ned to be in the right order.
*/

static void	start_players(t_vm *vm)
{
	unsigned	i;
	uint8_t		*player_start;
	t_player	*player;
	t_process	*inital_process;

	ft_vector_init(&vm->processes);
	i = 0;
	while (i < vm->player_count)
	{
		player = vm->players[i];
		annouce_player(player);
		player_start = vm->arena +
			(sizeof(vm->arena) / vm->player_count) * (player->number - 1);
		ft_memcpy(player_start, player->prog, player->header.prog_size);
		inital_process = ft_memalloc(sizeof(t_process));
		inital_process->executing = *player_start;
		inital_process->player_id = player->number; 
		if (inital_process->executing >= 0 && inital_process->executing < 16)
			inital_process->cycles_left =
				g_op_tab[inital_process->executing].cycles - 1;
		ft_vector_push(&vm->processes, inital_process);
		++i;
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
