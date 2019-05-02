/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:19:25 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/01 19:24:23 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H
# include "op.h"
# include "libft.h"

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
** Process specific memory.
*/

# define PRO_V(x) p->val_pro[x] - 1

typedef struct		s_process {
	t_player		*player;
	unsigned		pc;
	unsigned		last_live_cycle;
	int32_t			registers[REG_NUMBER];
	uint32_t		execute_cycle;
	unsigned char	type_proc[3];
	int				val_pro[3];
	uint8_t			executing;
	bool			carry;
}					t_process;

void			process_fork(t_process *p);

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

# define P1(byte) ((byte & 0b11000000) >> 6)
# define P2(byte) ((byte & 0b00110000) >> 4)
# define P3(byte) ((byte & 0b00001100) >> 2)

/*
** Get parameter type of parameter x, parameters are 1 indexed.
*/
# define PX(byte, X) ((byte & (192 >> ((X - 1) * 2))) >> (8 - (X * 2)))

# define REG 0b01
# define DIR 0b10
# define IND 0b11

# define ARENA(vm, i) vm->arena[(unsigned)(i) % MEM_SIZE]
# define PROC(vm, i) ((t_process*)vm->processes.data[i])

void			vm_init(t_vm *vm);
void			vm_run(t_vm *vm);
void			vm_del(t_vm *vm);
void			parse_options(int argc, char **argv, t_vm *vm);
void			exit_usage(t_vm *vm);
void			load_player(t_vm *vm, char *fp, unsigned n);

/*
** Instruction functions
*/

int		live(t_vm *vm, t_process *process);
bool	ld(t_vm *vm, t_process *p);
bool	st(t_vm *vm, t_process *p);
bool	add(t_vm *vm, t_process *p);
bool	sub(t_vm *vm, t_process *p);
bool	and(t_vm *vm, t_process *p);
bool	or(t_vm *vm, t_process *p);
bool	xor(t_vm *vm, t_process *p);
bool	zjmp(t_vm *vm, t_process *p);
bool	ldi(t_vm *vm, t_process *p);
bool	sti(t_vm *vm, t_process *p);
bool	fork(t_vm *vm, t_process *p);
bool	lld(t_vm *vm, t_process *p);
bool	lldi(t_vm *vm, t_process *p);
bool	lfork(t_vm *vm, t_process *p);
void	aff(t_vm *vm, t_process *p);

#endif
