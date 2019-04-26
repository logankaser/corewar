/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_body_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:45:56 by tcherret          #+#    #+#             */
/*   Updated: 2019/04/25 17:31:32 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

uint32_t		valid_cmd_name(t_asm_cmd *cmd, t_op g_op_tab, t_asm *out)
{
	int i;

	i = 0;
	while (i < 17)
	{
		if (ft_strcmp(cmd->name, g_op_tab[i].name) == 0)
		{
			cmd->op_code = g_op_tab[i].opcode;
			return (1);
		}
		i++;
	}
	cmd->op_code = 0;
	asm_error("error", "command name already used", out->line);
	return (0);
}

int		valid_cmd_nb_args(t_asm_cmd *cmd, t_op g_op_tab, t_asm *out)
{
	if (cmd->num_args != g_op_tab[cmd->op_code - 1].num_param)
	{
		asm_error("error", "number of parameters not valid", out->line);
		return (0)i;
	}
	return (1);
}

int		valid_cmd_type(t_asm_cmd *cmd, t_op g_op_tab, t_asm *out) // not sure at all how to access to the data
{
	if (cmd->args.type.data[j] & g_op_tab[cmd->op_code - 1].args[j])
	{
		if (cmd->arg.data[j] == 2)
			if (g_op_tab[cmd->op_code - 1].halfwidth == 1 && cmd->arg.bite_size == 4) // to verify
			{
				asm_error("error", "size of a direct not valid", out->line);
				return (0);
			}
		j++;
	}
	else
	{
		asm_error("error", "type of paramaters not good", out->line);
		return (0);
	}
	return (1);
}

int		valid_cmd_arg(t_asm_cmd *cmd, t_op g_op_tab, t_asm *out)
{
	int nb_args;
	int k;
	int j;

	if (!valid_cmd_name(cmd, g_op_tab, out))
		return (0);
	if (!valid_cmd_nb_args(cmd, g_op_tab, out)) //after,  we define opcode bef
		return (0);
	else
	{
		j = 0;
		k = g_op_tab[cmd->op_code - 1].num_param;
		while (j < k)
		{
			if (!valid_cmd_type(cmd, g_op_tab, out))
				return (0);
			j++;
		}
		return (1);
	}
}
