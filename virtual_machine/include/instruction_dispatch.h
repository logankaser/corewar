/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_dispatch.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:05:43 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/26 14:05:45 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTION_DISPATCH_H
# define INSTRUCTION_DISPATCH_H
# include "decode.h"
# include "virtual_machine.h"

typedef void			t_instruction(t_vm *vm, t_process *p, t_decode *d);

void					live(t_vm *vm, t_process *p, t_decode *d);
void					st(t_vm *vm, t_process *p, t_decode *d);
void					sti(t_vm *vm, t_process *p, t_decode *d);
void					ldi(t_vm *vm, t_process *p, t_decode *d);
void					lldi(t_vm *vm, t_process *p, t_decode *d);


extern t_instruction	*const g_instruction_dispatch[16];

#endif
