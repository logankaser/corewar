/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:46:04 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/06 15:13:37 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
#include "decode.h"

void	aff(t_vm *vm, t_process *p, t_decode *d)
{
	char	ascii;

	if (!vm->quiet)
	{
		ascii = param_read(d, vm->arena, p, 0) % 256;
		write(1, &ascii, 1);
	}
}
