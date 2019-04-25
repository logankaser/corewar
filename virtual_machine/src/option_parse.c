#include <fcntl.h>

#include "virtual_machine.h"

static const char	*g_usage =
"usage: ./corewar [-dump nbr_cycles] [[-n number] <champ.cor>]";

static void			exit_usage(t_vm *vm)
{
	vm_del(vm);
	ft_exit(g_usage, 1);
}

static void			load_warrior(char* fp, t_vm *vm, int n)
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
	magic_number = ft_byteswap4(magic_number);
	if (magic_number != COREWAR_EXEC_MAGIC)
	{
		ft_fprintf(stderr, "corewar: bad magic number in \"%s\"\n", fp);
		exit_usage(vm);
	}
	// Load warrior into vm.
}

static int		find_empty_slot(t_vm *vm)
{
	(void)vm;
	return 0;
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