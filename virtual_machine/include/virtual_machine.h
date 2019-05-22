/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:19:25 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/20 20:51:50 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H
# include "op.h"
# include "libft.h"

/*
** Player.
*/

typedef struct			s_player {
	t_header			header;
	uint8_t				prog[CHAMP_MAX_SIZE];
	int32_t				id;
	unsigned			last_live_cycle;
}						t_player;

# define NONE 0

/*
** Process specific memory.
*/

typedef struct			s_process {
	struct s_process	*next;
	unsigned			pc;
	unsigned			execute_cycle;
	unsigned			step;
	unsigned			last_live_cycle;
	unsigned			id;
	int32_t				registers[REG_NUMBER];
	uint8_t				executing;
	bool				carry;
	int32_t				owner;
}						t_process;

/*
** Virtual machine state.
*/

typedef struct			s_vm {
	unsigned			cycle;
	unsigned			dump_cycle;
	t_player			*players[MAX_PLAYERS];
	t_process			*processes;
	unsigned			lives;
	unsigned			checks;
	unsigned			player_count;
	unsigned			cycles_to_die;
	unsigned			check_cycle;
	uint8_t				arena[MEM_SIZE];
	bool				quiet;
	bool				visual;
}						t_vm;

# define VALID_REG(x) (x > 0 && x <= REG_NUMBER)
# define ARENA(vm, i) vm->arena[(unsigned)(i) % MEM_SIZE]
# define PROC(vm, i) ((t_process*)vm->processes.data[i])

void					vm_init(t_vm *vm);
void					vm_run(t_vm *vm);
void					vm_del(t_vm *vm);
void					parse_options(int argc, char **argv, t_vm *vm);
void					exit_usage(t_vm *vm);
void					load_player(t_vm *vm, char *fp, int32_t n);

#endif
