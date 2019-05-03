/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_dispatch.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:05:43 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/03 15:46:43 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTION_DISPATCH_H
# define INSTRUCTION_DISPATCH_H
# include "decode.h"
# include "virtual_machine.h"

typedef void			t_instruction(
	t_vm *vm, t_process *p, t_instruction_meta *im);

void					live(t_vm *vm, t_process *p, t_instruction_meta *im);
void					ld(t_vm *vm, t_process *p, t_instruction_meta *im);
void					add(t_vm *vm, t_process *p, t_instruction_meta *im);
void					sub(t_vm *vm, t_process *p, t_instruction_meta *im);
void					and(t_vm *vm, t_process *p, t_instruction_meta *im);
void					or(t_vm *vm, t_process *p, t_instruction_meta *im);
void					xor(t_vm *vm, t_process *p, t_instruction_meta *im);
void					zjmp(t_vm *vm, t_process *p, t_instruction_meta *im);
bool					ldi(t_vm *vm, t_process *p, t_instruction_meta *im);
bool					sti(t_vm *vm, t_process *p, t_instruction_meta *im);
void					fork(t_vm *vm, t_process *p, t_instruction_meta *im);
bool					lld(t_vm *vm, t_process *p, t_instruction_meta *im);
bool					lldi(t_vm *vm, t_process *p, t_instruction_meta *im);
bool					lfork(t_vm *vm, t_process *p, t_instruction_meta *im);
void					aff(t_vm *vm, t_process *p, t_instruction_meta *im);

extern t_instruction	*const g_instruction_dispatch[16];

#endif
