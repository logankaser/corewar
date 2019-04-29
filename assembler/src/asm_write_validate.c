/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:00:54 by jbeall            #+#    #+#             */
/*   Updated: 2019/04/28 21:04:50 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		validate_label(char *label, int len, t_asm *out)
{
	char	*name;
	t_label	*new;

	name = ft_strnew(len);
	ft_strncpy(name, label, len);
	if (!len)
		asm_error("syntax error", "invalid label", out->line);
	if (ft_map_get(LABEL_MAP(out), name))
		asm_error("error", "label already exists", out->line);
	new = ft_memalloc(sizeof(t_label));
	new->label_name = name;
	new->label_id = ++out->num_label;
	new->mem_addr = out->mem_ptr;
	ft_map_set(LABEL_MAP(out), name, new);
	return (ft_strlen(name) + 1);
}

char		*parse_arg_reg(char *line, t_asm *out, t_asm_arg *new)
{
	int		i;
	char	*tmp;

	new->type = T_REG;
	new->byte_size = 1;
	i = 0;
	if (!(*line >= '0' && *line <= '9'))
		asm_error("syntax error", "invalid register character", out->line);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	tmp = ft_strnew(i + 1);
	ft_strlcat(tmp, line, i + 1);
	new->val = ft_atoi(tmp);
	if (new->val < 0 || new->val > REG_NUMBER)
		asm_error("error", "invalid register number", out->line);
	free(tmp);
	return (line + i);
}

unsigned	write_arg_data(t_asm *out, t_asm_arg *arg, unsigned ptr)
{
	uint8_t		one;
	uint16_t	two;
	uint32_t	four;

	if (arg->byte_size == 2)
	{
		two = reverse_endian_two((uint16_t)(arg->val));
		ft_memcpy(out->program + ptr, &two, 2);
		return (2);
	}
	else if (arg->byte_size == 4)
	{
		four = reverse_endian((uint32_t)(arg->val));
		ft_memcpy(out->program + ptr, &four, 4);
		return (4);
	}
	else
	{
		one = (uint8_t)arg->val;
		out->program[ptr] = one;
		return (1);
	}
}

void		write_cmd_data(t_asm *out)
{
	t_asm_cmd	*cmd;
	t_asm_arg	*arg;
	unsigned	ptr;
	unsigned	i;
	unsigned	j;

	i = 0;
	while (i < out->cmd_vec.length)
	{
		j = 0;
		cmd = ft_uvector_get(&out->cmd_vec, i);
		ptr = cmd->mem_addr;
		out->program[ptr++] = (uint8_t)cmd->op_code;
		if (cmd->has_encode)
			out->program[ptr++] = cmd->encode;
		while (j < cmd->num_args)
		{
			arg = ft_uvector_get(&cmd->args, j);
			ptr += write_arg_data(out, arg, ptr);
			j++;
		}
		i++;
	}
}
