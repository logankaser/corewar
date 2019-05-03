/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:32:37 by tcherret          #+#    #+#             */
/*   Updated: 2019/05/02 20:48:19 by tcherret         ###   ########.fr       */
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

void			write_header(t_disasm file_data)
{
	write(file_data.fdc, ".name \"", 7);
	ft_putstr_fd(file_data.header.prog_name, file_data.fdc);
	write(file_data.fdc, "\"\n", 2);
	write(file_data.fdc, ".comment \"", 10);
	ft_putstr_fd(file_data.header.comment, file_data.fdc);
	write(file_data.fdc, "\"\n\n", 3);
}

static uint8_t g_type[4] = {
	0,
	T_REG,
	T_DIR,
	T_IND
};

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

unsigned		encoded_size(uint8_t *arena, unsigned pc)
{
	uint8_t		opi;
	uint8_t		enc;
	uint8_t		size[4];

	opi = arena[pc % MEM_SIZE] - 1;
	size[0] = 0;
	size[REG] = 1;
	size[DIR] = DIR_SIZE - (g_op_tab[opi].halfwidth * 2);
	size[IND] = 2;
	if (!g_op_tab[opi].encoded)
		return (1 + size[DIR]);
	enc = arena[(pc + 1) % MEM_SIZE];
	if (g_op_tab[opi].param_num == 1)
		return (2 + size[P1(enc)]);
	else if (g_op_tab[opi].param_num == 2)
		return (2 + size[P1(enc)] + size[P2(enc)]);
	return (2 + size[P1(enc)] + size[P2(enc)] + size[P3(enc)]);
}

unsigned		write_program_op(uint8_t op, t_op *g_op_tab,
		t_disasm *file_data)
{
	if (op > 0 && op < 17)
	{
		ft_printf("%s  ", g_op_tab[op - 1].name);
		ft_putstr_fd(g_op_tab[op - 1].name, file_data->fdc);
		write(file_data->fdc, "  ", 2);
	}
	return (1);
}

unsigned		write_param(unsigned type, uint8_t op, t_op *g_op_tab,
		t_disasm *file_data)
{
	int64_t	param;

	param = 0;
	if (type == REG_CODE)
	{
		ft_memcpy(&param, file_data->program + file_data->index, 1);
		ft_printf("r%d ", param);
		write(file_data->fdc, "r", 1);
		ft_putnbr_fd(param, file_data->fdc);
		write(file_data->fdc, " ", 1);
		return (1);
	}
	else if (type == IND_CODE)
	{
		ft_memcpy(&param, file_data->program + file_data->index, 2);
		param = ft_byteswap2(param);
		ft_printf(":%d ", param);
		write(file_data->fdc, ":", 1);
		ft_putnbr_fd(param, file_data->fdc);
		write(file_data->fdc, " ", 1);
		return (2);
	}
	else if (type == DIR_CODE && g_op_tab[op - 1].halfwidth == 0)
	{
		ft_memcpy(&param, file_data->program + file_data->index, 4);
		param = ft_byteswap4(param);
		ft_printf("%%%d ", param);
		write(file_data->fdc, "%", 1);
		ft_putnbr_fd(param, file_data->fdc);
		write(file_data->fdc, " ", 1);
		return (4);
	}
	else if (type == DIR_CODE && g_op_tab[op - 1].halfwidth == 1)
	{
		ft_memcpy(&param, file_data->program + file_data->index, 2);
		param = ft_byteswap2(param);
		ft_printf("%%%d ", param);
		write(file_data->fdc, "%", 1);
		ft_putnbr_fd(param, file_data->fdc);
		write(file_data->fdc, " ", 1);
		return (2);
	}
	return (0);
}

unsigned		write_live_zjmp_fork(uint8_t op, t_disasm *file_data)
{
	int16_t	param;
	int32_t	param1;

	param = 0;
	if (op == 1)
	{
		ft_memcpy(&param1, file_data->program + file_data->index, 4);
		param1 = ft_byteswap4(param1);
		ft_printf("%%%d ", param1);
		write(file_data->fdc, "%", 1);
		ft_putnbr_fd(param1, file_data->fdc);
		write(file_data->fdc, " ", 1);
		return (4);
	}
	else if (op == 9 | op == 12 | op == 15)
	{
		ft_memcpy(&param, file_data->program + file_data->index, 2);
		param = ft_byteswap2(param);
		ft_printf("%%%d ", param);
		write(file_data->fdc, "%", 1);
		ft_putnbr_fd(param, file_data->fdc);
		write(file_data->fdc, " ", 1);
		return (2);
	}
	return (0);
}

unsigned		write_program(t_disasm *file_data, t_op *g_op_tab)
{
	uint8_t		op;
	unsigned	enc;

	enc = 0;
	if (!validate_types(file_data->program, file_data->index))
		return (encoded_size(file_data->program, file_data->index));
	ft_memcpy(&op, file_data->program + file_data->index, 1);
	file_data->index += write_program_op(op, g_op_tab, file_data);
	if (g_op_tab[op - 1].encoded == 1)
	{
		ft_memcpy(&enc, file_data->program + file_data->index, 1);
		file_data->index++;
		if (P1(enc))
			file_data->index += write_param(P1(enc), op, g_op_tab, file_data);
		if (P2(enc))
			file_data->index += write_param(P2(enc), op, g_op_tab, file_data);
		if (P3(enc))
			file_data->index += write_param(P3(enc), op, g_op_tab, file_data);
	}
	else
		file_data->index += write_live_zjmp_fork(op, file_data);
	ft_printf("\n");
	write(file_data->fdc, "\n", 1);
	return (0);
}

int				error_dis(char *str, char **name)
{
	ft_printf(RED_TEXT"%s\n"COLOR_RESET, str);
	free(*name);
	return (-1);
}

int				main(int ac, char **av)
{
	char		*name;
	t_uvector	file;
	t_disasm	file_data;

	if (ac != 2)
		ft_printf("usage: ./disasm <file.cor>\n");
	else
	{
		if (!basic_check(av[1]))
			return (-1);
		name = ft_strf("%s.dis", av[1]);
		if ((file_data.fdc = open(name, O_WRONLY | O_CREAT, 0644)) < 0
				|| !read_file(av[1], &file))
			return (error_dis("error: problem with the fd", &name));
		file_data.index = 0;
		ft_memcpy(&file_data.header, file.data, sizeof(t_header));
		file_data.header.prog_size = ft_byteswap4(file_data.header.prog_size);
		if (file_data.header.prog_size > CHAMP_MAX_SIZE)
			return (error_dis("error: file exceeds champ max size", &name));
		ft_memcpy(file_data.program, file.data + sizeof(t_header),
				file_data.header.prog_size);
		file_data.header.prog_name[PROG_NAME_LENGTH] = '\0';
		file_data.header.comment[COMMENT_LENGTH] = '\0';
		write_header(file_data);
		while (file_data.index < file_data.header.prog_size)
			file_data.index += write_program(&file_data, g_op_tab);
		close(file_data.fdc);
		ft_printf(GREEN_TEXT"\nWriting the output at /%s!\n"COLOR_RESET, name);
		free(name);
	}
	return (0);
}
