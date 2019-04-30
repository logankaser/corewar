/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 12:44:05 by jbeall            #+#    #+#             */
/*   Updated: 2019/04/28 21:20:16 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_print_arg(t_asm_arg *arg)
{
	static char *type[5] = {"", "T_REG", "T_DIR", "", "T_IND"};

	ft_printf(YELLOW_TEXT"type[%s] bsize[%d]"COLOR_RESET, type[arg->type],
			arg->byte_size);
	if (arg->use_label)
		ft_printf(YELLOW_TEXT" [:%s]\n"COLOR_RESET, arg->label_name);
	else
		ft_printf(YELLOW_TEXT" val[%d] \n"COLOR_RESET, arg->val);
}

void	asm_print_encode(uint8_t encode)
{
	uint8_t mask;

	mask = 1 << 7;
	while (mask)
	{
		ft_printf(BLUE_TEXT"%d"COLOR_RESET, mask & encode ? 1 : 0);
		mask >>= 1;
	}
}

void	asm_print_cmd(t_asm_cmd *cmd)
{
	unsigned i;

	i = 0;
	ft_printf(BLUE_TEXT"op: [%d] name: [%s] memaddr: [%d] "COLOR_RESET,
			cmd->op_code, cmd->name, cmd->mem_addr);
	ft_printf(BLUE_TEXT"encode ["COLOR_RESET);
	cmd->has_encode ? asm_print_encode(cmd->encode) : ft_printf("-");
	ft_printf(BLUE_TEXT"] numargs: [%d]\n"COLOR_RESET, cmd->num_args);
	while (i < cmd->num_args)
	{
		ft_printf(YELLOW_TEXT"arg %d "COLOR_RESET, i);
		asm_print_arg((t_asm_arg*)ft_uvector_get(&cmd->args, i));
		i++;
	}
}

void	asm_print_labels(t_asm *data)
{
	unsigned	i;
	t_label		*lab;
	t_bucket	*current;

	i = 0;
	ft_printf(MAGENTA_TEXT"==LABELS==\n"COLOR_RESET);
	while (i < data->label_map.capacity)
	{
		current = data->label_map.data[i];
		while (current)
		{
			lab = current->value;
			ft_printf(BLUE_TEXT "id[%d] name[%s] memaddr[%u]\n" COLOR_RESET,
					lab->label_id, lab->label_name, lab->mem_addr);
			current = current->next;
		}
		i++;
	}
	ft_printf("\n");
}

void	asm_print_data(t_asm *data)
{
	unsigned i;

	i = 0;
	ft_printf(MAGENTA_TEXT"==DATA==\n"COLOR_RESET);
	ft_printf(BLUE_TEXT"num_labels [%d]\n"COLOR_RESET, data->num_label);
	ft_printf(BLUE_TEXT"num_cmd [%d]\n\n"COLOR_RESET, data->cmd_vec.length);
	asm_print_labels(data);
	ft_printf(MAGENTA_TEXT"==CMD==\n"COLOR_RESET);
	while (i < data->cmd_vec.length)
	{
		asm_print_cmd((t_asm_cmd*)ft_uvector_get(&data->cmd_vec, i));
		ft_printf("\n");
		i++;
	}
}
