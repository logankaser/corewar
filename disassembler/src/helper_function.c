/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:41:43 by tcherret          #+#    #+#             */
/*   Updated: 2019/05/03 13:46:33 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "disasm.h"

static uint8_t g_type[4] = {
	0,
	T_REG,
	T_DIR,
	T_IND
};

bool			read_file(const char *filepath, t_uvector *buf)
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

bool			validate_types(uint8_t *arena, unsigned pc)
{
	uint8_t opi;
	uint8_t enc;
	uint8_t valid_count;

	opi = arena[pc % MEM_SIZE] - 1;
	if (!g_op_tab[opi].encoded)
		return (true);
	enc = arena[(pc + 1) % MEM_SIZE];
	valid_count = 0;
	if (g_type[P1(enc)] & g_op_tab[opi].param_types[0])
		valid_count += 1;
	if (g_type[P2(enc)] & g_op_tab[opi].param_types[1])
		valid_count += 1;
	if (g_type[P3(enc)] & g_op_tab[opi].param_types[2])
		valid_count += 1;
	return (g_op_tab[opi].param_num == valid_count);
}
