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
# include "virtual_machine.h"

typedef void			t_instruction(uint8_t *arena, t_process *p);

extern t_instruction	*g_instruction_dispatch[16];

#endif
