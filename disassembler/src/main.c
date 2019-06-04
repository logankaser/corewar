/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:32:37 by tcherret          #+#    #+#             */
/*   Updated: 2019/06/04 13:41:48 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "disasm.h"

static bool	copy_player(t_uvector file, t_disasm *player, char *fp)
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
			"corewar: program size is corrupt in \"%s\""
			", claim: %i, actual: %i\n",
			fp, player->header.prog_size, file.length - HEADER_SIZE);
		return (false);
	}
	ft_memcpy(player->program,
		file.data + sizeof(t_header), player->header.prog_size);
	player->header.prog_name[PROG_NAME_LENGTH] = '\0';
	player->header.comment[COMMENT_LENGTH] = '\0';
	return (true);
}

static void	load_player_file(char *fp, t_disasm *player)
{
	t_uvector	file;

	if (!read_file(fp, &file))
	{
		ft_fprintf(stderr, "disasm: could not open \"%s\"\n", fp);
		exit(1);
	}
	else if (((int)file.length) - HEADER_SIZE > CHAMP_MAX_SIZE)
	{
		ft_fprintf(stderr, "disasm: program \"%s\" is too large\n", fp);
		free(file.data);
		exit(2);
	}
	else if (file.length <= HEADER_SIZE)
	{
		ft_fprintf(stderr, "disasm: program \"%s\" is too small\n", fp);
		free(file.data);
		exit(3);
	}
	if (!copy_player(file, player, fp))
	{
		free(file.data);
		exit(4);
	}
	free(file.data);
}

static int	finish_dis(char *str, char *name, int k)
{
	if (k == 0)
		ft_printf(GREEN_TEXT"%s %s!\n"COLOR_RESET, str, name);
	else
		ft_printf(RED_TEXT"%s\n"COLOR_RESET, str);
	free(name);
	return (k);
}

static int	usage_dis(void)
{
	ft_printf("usage: ./disasm <file.cor>\n");
	return (-1);
}

int			main(int ac, char **av)
{
	char		*name;
	t_disasm	file_data;

	if (ac != 2)
		return (usage_dis());
	name = ft_strf("%s.dis", av[1]);
	if ((file_data.fdc = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		finish_dis(
			RED_TEXT"Error: could not open output file"COLOR_RESET, name, -1);
		return (-1);
	}
	load_player_file(av[1], &file_data);
	write_header(&file_data);
	file_data.index = 0;
	while (file_data.index < file_data.header.prog_size)
		file_data.index += write_program(&file_data);
	close(file_data.fdc);
	return (finish_dis("Writing the output at", name, 0));
}
