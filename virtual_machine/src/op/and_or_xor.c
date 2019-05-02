/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:02:59 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/01 18:47:10 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

bool    and(t_vm *vm, t_process *p)
{
    int i;
    int vals[3];

    i = 0;
    while (i < 2)
    {
        if (p->type_proc[i] == IND_CODE)
            //FIXME: Add the value for IND_CODE after Logn
        else if (p->type_proc[i] == DIR_CODE)
            //FIXME: Add the value for DIR_CODE after Logn
        else if (p->type_proc[i] == REG_CODE)
            //FIXME: Add the value for REG_CODE after Logn
    }
    vals[2] = vals[1] & vals[2];
    p->registers[REG(2)] = value[2];
    if (p->registers[REG(2)])
        p->carry = 0;
    p->carry = 1;
    return (p->carry);
}

bool    or(t_vm *vm, t_process *p)
{
    int i;
    int vals[3];

    i = 0;
    while (i < 2)
    {
        if (p->type_proc[i] == IND_CODE)
            //FIXME: Add the value for IND_CODE after Logn
        else if (p->type_proc[i] == DIR_CODE)
            //FIXME: Add the value for DIR_CODE after Logn
        else if (p->type_proc[i] == REG_CODE)
            //FIXME: Add the value for REG_CODE after Logn
    }
    vals[2] = vals[1] | vals[2];
    p->registers[REG(2)] = value[2];
    if (p->registers[REG(2)])
        p->carry = 0;
    p->carry = 1;
    return (p->carry);
}

bool    xor(t_vm *vm, t_process *p)
{
    int i;
    int vals[3];

    i = 0;
    while (i < 2)
    {
        if (p->type_proc[i] == IND_CODE)
            //FIXME: Add the value for IND_CODE after Logn
        else if (p->type_proc[i] == DIR_CODE)
            //FIXME: Add the value for DIR_CODE after Logn
        else if (p->type_proc[i] == REG_CODE)
            //FIXME: Add the value for REG_CODE after Logn
    }
    vals[2] = vals[1] ^ vals[2];
    p->registers[REG(2)] = value[2];
    if (p->registers[REG(2)])
        p->carry = 0;
    p->carry = 1;
    return (p->carry);
}
