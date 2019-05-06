/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 18:34:18 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/03 18:34:20 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H
# include "virtual_machine.h"

t_process	*process_spawn(t_vm *vm, t_process *parent, unsigned pc);
void		process_check(t_vm *vm, t_process **p);

#endif
