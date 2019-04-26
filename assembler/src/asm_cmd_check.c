/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_body_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:45:56 by tcherret          #+#    #+#             */
/*   Updated: 2019/04/26 13:42:22 by tcherret         ###   ########.fr       */
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
	asm_error("syntax error", "command is not valid", out->line);
	return (0);
}

int		valid_cmd_nb_args(t_asm_cmd *cmd, t_op g_op_tab, t_asm *out)
{
	if (cmd->num_args != g_op_tab[cmd->op_code - 1].num_param)
		asm_error("arg error", "number of parameters not valid", out->line);
	return (1);
}

int		valid_cmd_type(t_asm_cmd *cmd, t_op g_op_tab, t_asm *out, int j) // not sure at all how to access to the data
{
	if (cmd->args.type.data[j] & g_op_tab[cmd->op_code - 1].args[j])
	{
		if (cmd->arg.data[j] == 2)
			if (g_op_tab[cmd->op_code - 1].halfwidth == 1 && cmd->arg.bite_size == 4) // to verify
				cmd->arg.bite_size = 2;
	}
	else
		asm_error("arg error", "type of a parameter not good", out->line);
	return (1);
}

int		valid_cmd_arg(t_asm_cmd *cmd, t_op g_op_tab, t_asm *out)
{
	int nb_args;
	int k;
	int j;

	if (!valid_cmd_name(cmd, g_op_tab, out))
		return (0);
	if (!valid_cmd_nb_args(cmd, g_op_tab, out))
		return (0);
	else
	{
		j = 0;
		k = g_op_tab[cmd->op_code - 1].num_param;
		while (j < k)
		{
			if (!valid_cmd_type(cmd, g_op_tab, out, j))
				return (0);
			j++;
		}
		return (1);
	}
}


//--------------------//


int		check_file_type(char *str)
{
	int size;

	size = ft_strlen(str);
	if (str[size - 1] != 's' || str[size - 2] != '.')
	{
		asm_error("file error", "file must be '.s'", 0);
		return (0);
	}
	return (1);
}
