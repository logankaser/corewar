/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:46:04 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/03 14:12:35 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	aff(t_vm *vm, t_process *p, t_instruction_meta *im)
{
	unsigned char ascii;

	ascii = param_load(im, vm->arenam, p->pc, 0) % 256; // do we need to do more check on the ascii?
	if (ft_isascii(ascii))
		ft_printf("%c\n", ascii);
}
