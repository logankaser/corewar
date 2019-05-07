/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_cmd_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:45:56 by tcherret          #+#    #+#             */
/*   Updated: 2019/05/07 13:51:33 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "asm.h"
#include "op.h"

uint32_t	valid_cmd_name(t_asm_cmd *cmd, t_asm *out)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(cmd->name, g_op_tab[i].name) == 0)
		{
			cmd->op_code = g_op_tab[i].opcode;
			return (1);
		}
		i++;
	}
	asm_error("syntax error", "command is not valid", out->line);
	return (0);
}

int			valid_cmd_nb_args(t_asm_cmd *cmd, t_asm *out)
{
	if (cmd->num_args != g_op_tab[cmd->op_code - 1].param_num)
		asm_error("arg error", "number of parameters not valid", out->line);
	return (1);
}

int			valid_arg_type(t_asm_cmd *cmd, t_asm *out, int j)
{
	t_asm_arg *arg;

	arg = (t_asm_arg*)ft_uvector_get(&cmd->args, j);
	if (g_op_tab[cmd->op_code - 1].encoded == 1)
		cmd->has_encode = 1;
	if (arg->type & g_op_tab[cmd->op_code - 1].param_types[j])
	{
		if (arg->type == T_DIR)
			if (g_op_tab[cmd->op_code - 1].halfwidth == 1
				&& arg->byte_size == 4)
				arg->byte_size = 2;
	}
	else
		asm_error("arg error", "type of a parameter not good", out->line);
	return (1);
}

int			valid_cmd(t_asm_cmd *cmd, t_asm *out)
{
	int k;
	int j;

	if (!valid_cmd_name(cmd, out))
		return (0);
	if (!valid_cmd_nb_args(cmd, out))
		return (0);
	j = 0;
	k = g_op_tab[cmd->op_code - 1].param_num;
	while (j < k)
	{
		if (!valid_arg_type(cmd, out, j))
			return (0);
		j++;
	}
	return (1);
}
