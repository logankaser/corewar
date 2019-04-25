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

#include <fcntl.h>
#include <arpa/inet.h>
#include "libft.h"
#include "virtual_machine.h"
#include "instruction_dispatch.h"

void				vm_init(t_vm *vm)
{
	vm->cycle = 0;
	vm->dump_cycle = 0;
	ft_vector_init(&vm->players);
	ft_bzero(&vm->arena, MEM_SIZE);
}

void				vm_del(t_vm *vm)
{
	unsigned i;

	i = 0;
	while (i < vm->players.length)
	{
		free(((t_player*)vm->players.data[i])->processes.data);
		++i;
	}
	ft_vector_del(&vm->players);
}

static const char	*g_usage =
"usage: ./corewar [-dump nbr_cycles] [[-n number] <champ.cor>]";

void				exit_usage(t_vm *vm)
{
	vm_del(vm);
	ft_exit(g_usage, 1);
}

void				load_warrior(char* fp, t_vm *vm, unsigned n)
{
	int			fd;
	unsigned	magic_number;

	(void)n;
	if ((fd = open(fp, O_RDONLY)) < 0)
	{
		ft_fprintf(stderr, "corewar: invalid warrior file \"%s\"\n", fp);
		exit_usage(vm);
	}
	magic_number = 0;
	read(fd, &magic_number, 4);
	magic_number = ntohl(magic_number);
	if (magic_number != COREWAR_EXEC_MAGIC)
	{
		ft_fprintf(stderr, "corewar: bad magic number in \"%s\"\n", fp);
		exit_usage(vm);
	}
	// Load warrior into vm.
}

unsigned find_empty_slot(t_vm *vm)
{
	(void)vm;
	return 0;
}

void				parse_arguments(int argc, char **argv, t_vm *vm)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-dump") || !ft_strcmp(argv[i], "--dump"))
		{
			i += 1;
			if (i >= argc || !ft_isdigit(argv[i][0]))
			{
				ft_fprintf(stderr,
					"corewar: --dump requires a number argument\n");
				exit_usage(vm);
			}
			vm->dump_cycle = ft_atoi(argv[i]);
		}
		else if (!ft_strcmp(argv[i], "-n"))
		{
			i += 1;
			if (i >= argc || !ft_isdigit(argv[i][0]))
			{
				ft_fprintf(stderr, "corewar: -n requires a number argument\n");
				exit_usage(vm);
			}
			i += 1;
			if (i >= argc)
			{
				ft_fprintf(stderr,
					"corewar: -n must be followed by warrior filepath\n");
				exit_usage(vm);
			}
			load_warrior(argv[i], vm, ft_atoi(argv[i - 1]));
		}
		else if (!ft_strncmp(argv[i], "-", 1))
		{
			ft_fprintf(stderr, "corewar: illegal option \"%s\"\n", argv[i]);
			exit_usage(vm);
		}
		else
		{
			load_warrior(argv[i], vm, find_empty_slot(vm));
		}
		++i;
	}
	if (vm->players.length == 0)
	{
		ft_fprintf(stderr, "corewar: no players!\n");
		exit_usage(vm);
	}
}

int					main(int argc, char **argv)
{
	t_vm vm;

	if (argc == 1)
		ft_exit(g_usage, 1);
	vm_init(&vm);
	parse_arguments(argc, argv, &vm);
	ft_printf("vm.dump_cycle: %i\n", vm.dump_cycle);
	// g_instruction_dispatch[0](NULL, NULL);
	ft_putendl(g_op_tab[0].name);
	vm_del(&vm);
}
