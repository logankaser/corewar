/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:05:23 by tcherret          #+#    #+#             */
/*   Updated: 2019/05/03 13:56:15 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

void			write_header(t_disasm *file_data)
{
	file_data->header.prog_name[PROG_NAME_LENGTH] = '\0';
	file_data->header.comment[COMMENT_LENGTH] = '\0';
	write(file_data->fdc, ".name \"", 7);
	ft_putstr_fd(file_data->header.prog_name, file_data->fdc);
	write(file_data->fdc, "\"\n", 2);
	write(file_data->fdc, ".comment \"", 10);
	ft_putstr_fd(file_data->header.comment, file_data->fdc);
	write(file_data->fdc, "\"\n\n", 3);
}

unsigned		write_program_op(uint8_t op, t_op *g_op_tab,
		t_disasm *file_data)
{
	if (op > 0 && op < 17)
	{
		ft_putstr_fd(g_op_tab[op - 1].name, file_data->fdc);
		write(file_data->fdc, "  ", 2);
	}
	return (1);
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
		write(file_data->fdc, "%", 1);
		ft_putnbr_fd(param1, file_data->fdc);
		write(file_data->fdc, " ", 1);
		return (4);
	}
	else if (op == 9 | op == 12 | op == 15)
	{
		ft_memcpy(&param, file_data->program + file_data->index, 2);
		param = ft_byteswap2(param);
		write(file_data->fdc, "%", 1);
		ft_putnbr_fd(param, file_data->fdc);
		write(file_data->fdc, " ", 1);
		return (2);
	}
	return (0);
}

unsigned		wrong_cor(void)
{
	ft_printf(RED_TEXT"Error: the cor file is not valid"COLOR_RESET);
	exit(-1);
	return (-1);
}

unsigned		write_program(t_disasm *file_data, t_op *g_op_tab)
{
	uint8_t		op;
	unsigned	enc;

	enc = 0;
	if (!validate_types(file_data->program, file_data->index))
		return (wrong_cor());
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
	write(file_data->fdc, "\n\0", 2);
	return (0);
}
