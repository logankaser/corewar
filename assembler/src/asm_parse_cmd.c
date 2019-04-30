/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:53:56 by jbeall            #+#    #+#             */
/*   Updated: 2019/04/28 20:57:48 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*parse_cmd_inner(char *line, t_asm *out, t_asm_cmd *new)
{
	while (*line && new->num_args < 4)
	{
		line = skip_space(line);
		if (*line == COMMENT_CHAR || *line == ';')
			break ;
		if (new->num_args && *line++ != SEPARATOR_CHAR)
			asm_error("syntax error", "no separator char", out->line);
		line = skip_space(line);
		line = parse_arg(line, out, new);
		line = skip_space(line);
		++new->num_args;
	}
	return (line);
}

char	*parse_cmd(char *line, t_asm *out)
{
	char		*cmd_name;
	t_asm_cmd	*new;
	int			len;

	len = 0;
	while (line[len] && ft_strchr(LABEL_CHARS, line[len]))
		len++;
	cmd_name = ft_strndup(line, len);
	new = ft_memalloc(sizeof(t_asm_cmd));
	new->name = cmd_name;
	new->mem_addr = out->mem_ptr;
	ft_uvector_init(&(new->args), sizeof(t_asm_arg));
	line += len;
	line = parse_cmd_inner(line, out, new);
	valid_cmd(new, g_op_tab, out);
	new->encode = new->has_encode ? encode_byte(new) : 0;
	out->mem_ptr += calc_cmd_size(new);
	ft_uvector_push(&(out->cmd_vec), new);
	return (line);
}

int		calc_cmd_size(t_asm_cmd *cmd)
{
	int			size;
	t_asm_arg	*arg;
	unsigned	i;

	size = 1;
	i = 0;
	if (cmd->has_encode)
		size += 1;
	while (i < cmd->num_args)
	{
		arg = (t_asm_arg*)ft_uvector_get(&cmd->args, i);
		size += arg->byte_size;
		i++;
	}
	return (size);
}

uint8_t	encode_byte(t_asm_cmd *cmd)
{
	unsigned	i;
	unsigned	shift;
	t_asm_arg	*arg;
	uint8_t		encode;
	uint8_t		type_encode;

	i = 0;
	encode = 0;
	shift = 6;
	while (i < cmd->num_args)
	{
		arg = ft_uvector_get(&cmd->args, i);
		if (arg->type == T_DIR)
			type_encode = DIR_CODE;
		else if (arg->type == T_IND)
			type_encode = IND_CODE;
		else
			type_encode = REG_CODE;
		encode |= type_encode << shift;
		shift -= 2;
		i++;
	}
	return (encode);
}

void	deref_labels(t_asm *out)
{
	t_asm_cmd	*cmd;
	t_asm_arg	*arg;
	t_label		*lab;
	unsigned	i;
	unsigned	j;

	i = 0;
	while (i < out->cmd_vec.length)
	{
		j = 0;
		cmd = ft_uvector_get(&out->cmd_vec, i);
		while (j < cmd->num_args)
		{
			arg = ft_uvector_get(&cmd->args, j);
			if (arg->use_label)
			{
				if (!(lab = ft_map_get(&out->label_map, arg->label_name)))
					asm_error("error", "label not found", out->line);
				arg->val = lab->mem_addr - cmd->mem_addr;
			}
			j++;
		}
		i++;
	}
}
