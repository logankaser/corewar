/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:47:49 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/25 16:47:50 by lkaser           ###   ########.fr       */
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

static unsigned		find_empty_slot(t_vm *vm)
{
	unsigned	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (!vm->players[i])
			break ;
		++i;
	}
	if (i != MAX_PLAYERS)
		return (i + 1);
	vm_del(vm);
	ft_exit("corewar: too many players, no empty slots", 1);
	return (0);
}

void				parse_options(int argc, char **argv, t_vm *vm)
{
	int i;

	if (argc == 1)
		exit_usage(vm);
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
			if (i >= argc || !ft_isdigit(argv[i][0])
				|| ft_atoi(argv[i]) >= MAX_PLAYERS)
			{
				ft_fprintf(stderr, "corewar: -n requires a valid number\n");
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
		}
		else if (!ft_strncmp(argv[i], "-", 1))
		{
			ft_fprintf(stderr, "corewar: illegal option \"%s\"\n", argv[i]);
			exit_usage(vm);
		}
		else
			load_player(vm, argv[i], find_empty_slot(vm));
		++i;
	}
	if (vm->player_count == 0)
	{
		ft_fprintf(stderr, "corewar: no players!\n");
		exit_usage(vm);
	}
}
