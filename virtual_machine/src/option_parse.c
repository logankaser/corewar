/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:47:49 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/21 12:31:29 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static const char	*g_usage =
"usage: ./corewar [-dump nbr_cycles] [[-n number] <champ.cor>]";

void				exit_usage(t_vm *vm)
{
	vm_del(vm);
	ft_exit(g_usage, 1);
}

static int32_t		find_free_id(t_vm *vm)
{
	unsigned	i;
	int32_t		id;

	if (vm->player_count == 0)
		return (1);
	id = vm->players[vm->player_count - 1]->id + 1;
	i = 0;
	while (i < vm->player_count)
	{
		if (vm->players[i]->id == id)
		{
			i = 0;
			id += 1;
			continue ;
		}
		++i;
	}
	return (id);
}

static int			parse_option_id(int argc, char **argv, int i, t_vm *vm)
{
	i += 1;
	if (i >= argc)
	{
		ft_fprintf(stderr, "corewar: -n requires a number\n");
		exit_usage(vm);
	}
	i += 1;
	if (i >= argc)
	{
		ft_fprintf(stderr,
			"corewar: -n must be followed by player filepath\n");
		exit_usage(vm);
	}
	load_player(vm, argv[i], ft_atoi(argv[i - 1]));
	return (i);
}

static int			parse_option_dump(int argc, char **argv, int i, t_vm *vm)
{
	i += 1;
	if (i >= argc || !ft_isdigit(argv[i][0]))
	{
		ft_fprintf(stderr,
			"corewar: --dump requires a number argument\n");
		exit_usage(vm);
	}
	vm->dump_cycle = ft_atoi(argv[i]);
	return (i);
}

void				parse_options(int argc, char **argv, t_vm *vm)
{
	int i;

	if (argc == 1)
		exit_usage(vm);
	i = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-d") || !ft_strcmp(argv[i], "--dump"))
			i = parse_option_dump(argc, argv, i, vm);
		else if (!ft_strcmp(argv[i], "-n"))
			i = parse_option_id(argc, argv, i, vm);
		else if (!ft_strcmp(argv[i], "-q") || !ft_strcmp(argv[i], "--quiet"))
			vm->quiet = true;
		else if (!ft_strcmp(argv[i], "-v"))
			vm->visual = true;
		else if (!ft_strncmp(argv[i], "-", 1))
		{
			ft_fprintf(stderr, "corewar: invalid option \"%s\"\n", argv[i]);
			exit_usage(vm);
		}
		else
			load_player(vm, argv[i], find_free_id(vm));
	}
}
