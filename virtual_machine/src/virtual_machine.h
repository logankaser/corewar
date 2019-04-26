/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:19:25 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/23 17:19:26 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H
# include "op.h"
# include "libft.h"

/*
** Process specific memory.
*/

typedef struct	s_process {
	unsigned	id;
	bool		carry;
	uint8_t		registers[REG_NUMBER][REG_SIZE];
	unsigned	pc;
	uint8_t		executing;
	uint8_t		cycles_left;
}				t_process;

/*
** Player.
*/

typedef struct	s_player {
	unsigned	number;
	int			last_live_cycle;
	char		*name;
	char		*comment;
	uint8_t		*source;
	unsigned	source_size;
	t_vector	processes;
}				t_player;

/*
** Virtual machine state.
*/

typedef struct	s_vm {
	unsigned	cycle;
	unsigned	dump_cycle;
	unsigned	cycles_to_die;
	t_player	*players[MAX_PLAYERS];
	unsigned	player_count;
	uint8_t		arena[MEM_SIZE];
}				t_vm;

void			vm_init(t_vm *vm);
void			vm_run(t_vm *vm);
void			vm_del(t_vm *vm);
void			parse_options(int argc, char **argv, t_vm *vm);

#endif
