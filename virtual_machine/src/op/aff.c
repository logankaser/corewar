/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:46:04 by ztisnes           #+#    #+#             */
/*   Updated: 2019/05/01 18:36:10 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void    aff(t_vm *vm, t_process *p)
{
    unsigned char ascii;
    //check params
    ascii = (p->registers[REG(0)] % 256);
    //print stuff from ascii?
}
