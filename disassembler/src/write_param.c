/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:08:17 by tcherret          #+#    #+#             */
/*   Updated: 2019/05/03 11:30:46 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

static unsigned	write_dir(unsigned type, uint8_t op, t_disasm *file_data)
{
	int64_t param;

	param = 0;
	if (type == DIR_CODE && g_op_tab[op - 1].halfwidth == 0)
	{
		ft_memcpy(&param, file_data->program + file_data->index, 4);
		param = ft_byteswap4(param);
		write(file_data->fdc, "%", 1);
		ft_putnbr_fd(param, file_data->fdc);
		write(file_data->fdc, " ", 1);
		return (4);
	}
	else if (type == DIR_CODE && g_op_tab[op - 1].halfwidth == 1)
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

unsigned		write_param(unsigned type, uint8_t op, t_disasm *file_data)
{
	int64_t	param;

	param = 0;
	if (type == REG_CODE)
	{
		ft_memcpy(&param, file_data->program + file_data->index, 1);
		write(file_data->fdc, "r", 1);
		ft_putnbr_fd(param, file_data->fdc);
		write(file_data->fdc, " ", 1);
		return (1);
	}
	else if (type == IND_CODE)
	{
		ft_memcpy(&param, file_data->program + file_data->index, 2);
		param = ft_byteswap2(param);
		write(file_data->fdc, ":", 1);
		ft_putnbr_fd(param, file_data->fdc);
		write(file_data->fdc, " ", 1);
		return (2);
	}
	else if (type == DIR_CODE)
		return (write_dir(type, op, file_data));
	return (0);
}
