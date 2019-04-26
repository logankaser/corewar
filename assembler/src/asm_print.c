/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 12:44:05 by jbeall            #+#    #+#             */
/*   Updated: 2019/04/26 13:16:14 by jbeall           ###   ########.fr       */
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

void asm_print_cmd(t_asm_cmd *cmd)
{
	int i;

	i = 0;
	ft_printf("op: [%d] name: [%s] memaddr: [%d] numargs: [%d]\n", cmd->op_code,
		cmd->name, cmd->mem_addr, cmd->num_args);
	while (i < cmd->num_args)
	{
		ft_printf("arg %d ", i);
		asm_print_arg((t_asm_arg*)ft_uvector_get(&cmd->args, i));
		i++;
	}
}

void asm_print_data(t_asm *data)
{
	unsigned i;

	i = 0;
	ft_printf("\n==DATA==\n");
	ft_printf("num_labels [%d]\n", data->num_label);
	ft_printf("num_cmd [%d]\n", data->cmd_vec.length);
	while (i < data->cmd_vec.length)
	{
		asm_print_cmd((t_asm_cmd*)ft_uvector_get(&data->cmd_vec, i));
		ft_printf("\n");
		i++;
	}
}
