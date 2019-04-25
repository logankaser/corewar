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
	int			cycles_to_live;
	t_uvector	processes;
}				t_player;

/*
** Virtual machine state.
*/

typedef struct	s_vm {
	unsigned	cycle;
	unsigned	dump_cycle;
	t_vector	players;
	uint8_t		arena[MEM_SIZE];
}				t_vm;

#endif
