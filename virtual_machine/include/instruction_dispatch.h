/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_dispatch.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:05:43 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/03 14:14:21 by tcherret         ###   ########.fr       */
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
void					lld(t_vm *vm, t_process *p, t_instruction_meta *im);
void					add(t_vm *vm, t_process *p, t_instruction_meta *im);
void					sub(t_vm *vm, t_process *p, t_instruction_meta *im);
void					aff(t_vm *vm, t_process *p, t_instruction_meta *im);


extern t_instruction	*const g_instruction_dispatch[16];

#endif
