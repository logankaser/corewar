/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:19:25 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/28 13:15:47 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H
# include "op.h"
# include "libft.h"
# include "decode.h"

/*
** Player.
*/

typedef struct			s_player {
	t_header			header;
	uint8_t				prog[CHAMP_MAX_SIZE];
	int32_t				id;
	int					last_live_cycle;
}						t_player;

# define NONE 0

/*
** Process specific memory.
*/

typedef struct			s_process {
	unsigned			pc;
	unsigned			last_live_cycle;
	int32_t				registers[REG_NUMBER];
	uint32_t			execute_cycle;
	struct s_process	*next;
	unsigned			step;
	uint8_t				executing;
	bool				carry;
}						t_process;

void					process_fork(t_process *p);

/*
** Virtual machine state.
*/

typedef struct			s_vm {
	unsigned			cycle;
	unsigned			dump_cycle;
	unsigned			cycles_to_die;
	t_player			*players[MAX_PLAYERS];
	unsigned			player_count;
	t_process			*processes;
	uint8_t				arena[MEM_SIZE];
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
