/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:48:34 by jbeall            #+#    #+#             */
/*   Updated: 2019/04/28 20:49:08 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char *parse_arg_lab(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		i++;
	tmp = ft_strndup(line, i);
	return (tmp);
}

char *parse_arg_set_label(t_asm_arg *new, char *line)
{
	new->use_label = 1;
	new->label_name = parse_arg_lab(++line);
	while (*line && ft_strchr(LABEL_CHARS, *line))
		line++;
	return (line);
}

char *parse_arg_set_direct(t_asm_arg *new, char *line)
{
	line++;
	new->type = T_DIR;
	new->byte_size = 4;
	return (line);
}

char *parse_arg_val(char *line, t_asm_arg *new)
{
	int		i;
	char	*tmp;

	i = 0;
	if (*line == DIRECT_CHAR)
		line = parse_arg_set_direct(new, line);
	else
	{
		new->type = T_IND;
		new->byte_size = 2;
	}
	if (*line == LABEL_CHAR)
		line = parse_arg_set_label(new, line);
	else
	{
		if (line[i] == '-')
			i++;
		while (line[i] >= '0' & line[i] <= '9')
			i++;
		tmp = ft_strndup(line, i);
		new->val = ft_atoi(tmp);
		free(tmp);
	}
	return (line + i);
}

char *parse_arg(char *line, t_asm *out, t_asm_cmd *cmd)
{
	t_asm_arg *new;

	new = ft_memalloc(sizeof(t_asm_arg));
	if (*line == 'r')
		line = parse_arg_reg(++line, out, new);
	else if (*line == DIRECT_CHAR || ft_strchr(NUM_CHARS, *line)
		|| *line == LABEL_CHAR)
		line = parse_arg_val(line, new);
	else
		asm_error("syntax error", "invalid arg", out->line);
	ft_uvector_push(&(cmd->args), new);
	return (line);
}
