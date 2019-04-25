/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:28:10 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/23 14:23:42 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "virtual_machine.h"
#include "instruction_dispatch.h"


int					main(int argc, char **argv)
{
	t_vm vm;

	vm_init(&vm);
	parse_options(argc, argv, &vm);
	ft_printf("vm.dump_cycle: %i\n", vm.dump_cycle);
	// g_instruction_dispatch[0](NULL, NULL);
	vm_del(&vm);
}
