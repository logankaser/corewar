/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:43:12 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/01 16:43:13 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static bool		copy_player(t_uvector file, t_player *player, char *fp)
{
	ft_memcpy(&player->header, file.data, sizeof(t_header));
	player->header.magic = ft_byteswap4(player->header.magic);
	if (player->header.magic != COREWAR_EXEC_MAGIC)
	{
		ft_fprintf(stderr, "corewar: bad magic number in \"%s\"\n", fp);
		return (false);
	}
	player->header.prog_size = ft_byteswap4(player->header.prog_size);
	if (player->header.prog_size != file.length - HEADER_SIZE)
	{
		ft_fprintf(stderr,
			"corewar: program size is corrupt in \"%s\", claim: %i, actual: %i\n",
			fp, player->header.prog_size, file.length - HEADER_SIZE);
		return (false);
	}
	ft_memcpy(player->prog,
		file.data + sizeof(t_header), player->header.prog_size);
	player->header.prog_name[PROG_NAME_LENGTH] = '\0';
	player->header.comment[COMMENT_LENGTH] = '\0';
	return (true);
}

static void		load_player_file(t_vm *vm, char *fp, t_player *player)
{
	t_uvector	file;

	if (!read_file(fp, &file))
	{
		ft_fprintf(stderr, "corewar: could not open \"%s\"\n", fp);
		exit_usage(vm);
	}
	else if (file.length - HEADER_SIZE > CHAMP_MAX_SIZE)
	{
		ft_fprintf(stderr, "corewar: program \"%s\" is too large \n", fp);
		exit_usage(vm);
	}
	else if (file.length <= HEADER_SIZE)
	{
		ft_fprintf(stderr, "corewar: program \"%s\" is too small in \n", fp);
		exit_usage(vm);
	}
	if (!copy_player(file, player, fp))
		exit_usage(vm);
}

void			load_player(t_vm *vm, char *fp, int32_t id)
{
	t_player *player;

	if (vm->player_count >= MAX_PLAYERS)
	{
		ft_fprintf(stderr, "corewar: too many players, no empty slots\n");
		exit_usage(vm);
	}
	vm->players[vm->player_count] = ft_memalloc(sizeof(t_player));
	player = vm->players[vm->player_count];
	player->id = id;
	player->last_live_cycle = 0;
	load_player_file(vm, fp, player);
	vm->player_count += 1;
}
