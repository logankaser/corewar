#include <fcntl.h>
#include "virtual_machine.h"

static bool		read_file(const char *filepath, t_uvector *buf)
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

static bool	load_warrior_header(t_uvector file, t_player *player)
{
	if (file.length - HEADER_SIZE > CHAMP_MAX_SIZE)
	{
		ft_fprintf(stderr, "error: program is too large\n");
		return (false);
	}
	if (player->header.prog_size != file.length - HEADER_SIZE)
	{
		ft_fprintf(stderr, "error: file size has been corrupted\n");
		return (false);
	}
	return (true);
}

static void		load_warrior_file(t_vm *vm, char *fp, t_player *player)
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
	if (error)
	{
		ft_fprintf(stderr, error, fp);
		exit_usage(vm);
	}
	if (!load_warrior_header(file, player))
		exit_usage(vm);
	ft_printf("SIZE: %u\n", player->header.prog_size);
}

void			load_warrior(t_vm *vm, char *fp, unsigned n)
{
	t_player *player;

	if (vm->players[n - 1])
	{
		ft_fprintf(stderr, "corewar: player %u already assigned\n", n);
		exit_usage(vm);
	}
	vm->players[n - 1] = ft_memalloc(sizeof(t_player));
	player = vm->players[n - 1];
	player->number = n;
	player->last_live_cycle = 0;
	load_warrior_file(vm, fp, player);
	vm->player_count += 1;
}
