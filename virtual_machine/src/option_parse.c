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

#include <fcntl.h>

#include "virtual_machine.h"

static const char	*g_usage =
"usage: ./corewar [-dump nbr_cycles] [[-n number] <champ.cor>]";

static void			exit_usage(t_vm *vm)
{
	vm_del(vm);
	ft_exit(g_usage, 1);
}

static bool			read_file(const char *filepath, t_uvector *buf)
{
	int			fd;
	ssize_t		ret;

	fd = STDIN_FILENO;
	if (filepath)
		fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (false);
	ft_uvector_init(buf, 1);
	while ((ret =
		read(fd, buf->data + buf->length, buf->capacity - buf->length)) > 0)
	{
		buf->length += ret;
		if (buf->capacity < buf->length + 1)
			ft_uvector_resize(buf, buf->capacity * 2);
	}
	close(fd);
	return (true);
}

static void			load_warrior_file(t_vm *vm, char *fp, t_player *player)
{
	unsigned	magic_number;
	t_uvector	file;
	char		*error;

	error = NULL;
	if (!read_file(fp, &file))
		error = "corewar: invalid warrior file \"%s\"\n";
	ft_memcpy(&magic_number, file.data, 4);
	if (ft_byteswap4(magic_number) != COREWAR_EXEC_MAGIC)
		error = "corewar: bad magic number in \"%s\"\n";
	else if (file.length <= sizeof(t_header))
		error = "corewar: warrior too small \"%s\"\n";
	else if (file.length - sizeof(t_header) > CHAMP_MAX_SIZE)
		error = "corewar: warrior too large \"%s\"\n";
	if (error)
	{
		ft_fprintf(stderr, error, fp);
		exit_usage(vm);
	}
	player->source = file.data + sizeof(t_header);
	player->source_size = file.length - sizeof(t_header);
}

static void			load_warrior(t_vm *vm, char *fp, unsigned n)
{
	t_player *player;

	if (vm->players[n - 1])
	{
		ft_fprintf(stderr, "corewar: player %u already assigned\n", n);
		exit_usage(vm);
	}
	vm->players[n - 1] = malloc(sizeof(t_player));
	player = vm->players[n - 1];
	player->number = n;
	player->last_live_cycle = 0;
	load_warrior_file(vm, fp, player);
	vm->player_count += 1;
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
					"corewar: -n must be followed by warrior filepath\n");
				exit_usage(vm);
			}
			load_warrior(vm, argv[i], ft_atoi(argv[i - 1]));
		}
		else if (!ft_strncmp(argv[i], "-", 1))
		{
			ft_fprintf(stderr, "corewar: illegal option \"%s\"\n", argv[i]);
			exit_usage(vm);
		}
		else
			load_warrior(vm, argv[i], find_empty_slot(vm));
		++i;
	}
	if (vm->player_count == 0)
	{
		ft_fprintf(stderr, "corewar: no players!\n");
		exit_usage(vm);
	}
}
