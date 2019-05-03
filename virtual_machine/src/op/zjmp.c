/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:51:53 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/03 14:39:31 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction_dispatch.h"

bool    zjmp(t_vm *vm, t_process *p, t_instruction_meta *im)
{
    if (vm && p->carry == 1)
        //new PC = PC + (value % IDX_MOD);
    else
        // new PC = PC + instruction_size
    return (p->pc)
}
