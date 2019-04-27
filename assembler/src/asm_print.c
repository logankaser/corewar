/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 12:44:05 by jbeall            #+#    #+#             */
/*   Updated: 2019/04/26 20:07:07 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void asm_print_arg(t_asm_arg *arg)
{
	static char *type[5] = {"", "T_REG", "T_DIR", "", "T_IND"};
	ft_printf("type[%s] bsize[%d]", type[arg->type], arg->byte_size);
	if (arg->use_label)
		ft_printf(" [:%s]\n", arg->label_name);
	else
		ft_printf(" val[%d] \n", arg->val);
}

void asm_print_encode(uint8_t encode)
{
	uint8_t mask;

	mask = 1 << 7;
	while (mask)
	{
		ft_printf("%d", mask & encode ? 1 : 0);
		mask >>= 1;
	}
}

void asm_print_cmd(t_asm_cmd *cmd)
{
	unsigned i;

	i = 0;
	ft_printf("op: [%d] name: [%s] memaddr: [%d] ", cmd->op_code, cmd->name, cmd->mem_addr);
	ft_printf("encode [");
	cmd->has_encode ? asm_print_encode(cmd->encode) : ft_printf("-");
	ft_printf("] numargs: [%d]\n", cmd->num_args);
	while (i < cmd->num_args)
	{
		ft_printf("arg %d ", i);
		asm_print_arg((t_asm_arg*)ft_uvector_get(&cmd->args, i));
		i++;
	}
}

void asm_print_labels(t_asm* data)
{
	unsigned i;
	t_label *lab;
	t_bucket *current;

	i = 0;
	ft_printf("==LABELS==\n");
	while (i < data->label_map.capacity)
	{
		current = data->label_map.data[i];
		while(current)
		{
			lab = current->value;
			ft_printf("id[%d] name[%s] memaddr[%u]\n", lab->label_id, lab->label_name, lab->mem_addr);
			current = current->next;
		}
		i++;
	}
	ft_printf("\n");
}

void asm_print_data(t_asm *data)
{
	unsigned i;

	i = 0;
	ft_printf("\n==DATA==\n");
	ft_printf("num_labels [%d]\n", data->num_label);
	ft_printf("num_cmd [%d]\n\n", data->cmd_vec.length);
	asm_print_labels(data);
	ft_printf("==CMD==\n");
	while (i < data->cmd_vec.length)
	{
		asm_print_cmd((t_asm_cmd*)ft_uvector_get(&data->cmd_vec, i));
		ft_printf("\n");
		i++;
	}
}
