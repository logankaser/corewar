/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:19:25 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/27 18:39:37 by tcherret         ###   ########.fr       */
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
	unsigned	player_id;
	bool		carry;
	uint32_t	registers[REG_NUMBER];
	unsigned	pc;
	uint8_t		executing;
	uint8_t		cycles_left;
}				t_process;

/*
** Player.
*/

typedef struct	s_player {
	t_header	header;
	uint8_t		prog[CHAMP_MAX_SIZE];
	unsigned	number;
	int			last_live_cycle;
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
	t_vector	processes;
	uint8_t		arena[MEM_SIZE];
}				t_vm;

void			vm_init(t_vm *vm);
void			vm_run(t_vm *vm);
void			vm_del(t_vm *vm);
void			parse_options(int argc, char **argv, t_vm *vm);
void			exit_usage(t_vm *vm);
void			load_warrior(t_vm *vm, char *fp, unsigned n);

#endif
