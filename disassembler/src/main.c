/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:32:37 by tcherret          #+#    #+#             */
/*   Updated: 2019/05/03 13:47:08 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

int				basic_check(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (file[len - 4] == '.')
		if (ft_strcmp(".cor", &file[len - 4]) == 0)
			return (1);
	return (-1);
}

int				finish_dis(char *str, char **name, int k)
{
	if (k == -1)
	{
		ft_printf(RED_TEXT"%s\n"COLOR_RESET, str);
		free(*name);
		return (-1);
	}
	else if (k == 0)
	{
		ft_printf(GREEN_TEXT"%s %s!\n"COLOR_RESET, str, *name);
		free(*name);
		return (0);
	}
	return (-1);
}

int				usage_dis(void)
{
	ft_printf("usage: ./disasm <file.cor>\n");
	return (-1);
}

int				main(int ac, char **av)
{
	char		*name;
	t_uvector	file;
	t_disasm	file_data;

	if (ac != 2)
		return (usage_dis());
	if (!basic_check(av[1]))
		return (-1);
	name = ft_strf("%s.dis", av[1]);
	if ((file_data.fdc = open(name, O_WRONLY | O_CREAT, 0644)) < 0
			|| !read_file(av[1], &file))
		return (finish_dis("error: problem with the fd", &name, -1));
	file_data.index = 0;
	ft_memcpy(&file_data.header, file.data, sizeof(t_header));
	file_data.header.prog_size = ft_byteswap4(file_data.header.prog_size);
	if (file_data.header.prog_size > CHAMP_MAX_SIZE)
		return (finish_dis("error: champ exceeds max size", &name, -1));
	ft_memcpy(file_data.program, file.data + sizeof(t_header),
			file_data.header.prog_size);
	write_header(&file_data);
	while (file_data.index < file_data.header.prog_size)
		file_data.index += write_program(&file_data, g_op_tab);
	close(file_data.fdc);
	return (finish_dis("Writing the output at", &name, 0));
}
