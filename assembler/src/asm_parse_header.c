/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:41:59 by jbeall            #+#    #+#             */
/*   Updated: 2019/04/28 16:07:57 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		capture_header_field(char *in, t_asm *out, char *field, size_t len)
{
	char *val;

	in = skip_space(in);
	if (!ft_strncmp(in, field, ft_strlen(field)))
	{
		in += ft_strlen(field);
		in = skip_space(in);
		if (*in == '"')
		{
			if (!(val = capture_to_quote(++in)))
				asm_error("syntax error", "no end quote", out->line);
			if (ft_strlen(val) > len)
				ft_exit("error: val exceeds length", 1);
			if (!ft_strcmp(field, NAME_CMD_STRING))
				ft_strlcat(out->header->prog_name, val, len);
			else if (!ft_strcmp(field, COMMENT_CMD_STRING))
				ft_strlcat(out->header->comment, val, len);
		}
		else
			asm_error("sytax error", "bad character", out->line);
	}
	else
		return (0);
	return (1);
}

int		contains_non_comment(char *st)
{
	st = skip_space(st);
	if (*st && *st != COMMENT_CHAR && *st != ';')
		return (1);
	return (0);
}

int		valid_header_block(t_uvector *block, t_asm *out)
{
	int			quote;
	unsigned	i;

	quote = 0;
	i = 0;
	while (i < block->length && quote < 2)
	{
		if (block->data[i] == '"')
			quote++;
		i++;
	}
	if (quote == 2 && contains_non_comment((char*)(block->data + i)))
		asm_error("syntax error", "bad character", out->line);
	if (quote == 2)
		return (1);
	return (0);
}

char	*capture_to_space(char *in)
{
	int			len;
	static char	buf[CAPTURE_BUFF];

	len = 0;
	ft_bzero(buf, CAPTURE_BUFF);
	while (in[len] && len < CAPTURE_BUFF - 1 && !ft_isspace(in[len]))
		len++;
	ft_strlcat(buf, in, CAPTURE_BUFF);
	return (buf);
}

char	*capture_to_quote(char *in)
{
	int			len;
	static char	buf[CAPTURE_BUFF];

	len = 0;
	ft_bzero(buf, CAPTURE_BUFF);
	while (in[len] && len < CAPTURE_BUFF - 1 && in[len] != '"')
		len++;
	ft_strlcat(buf, in, len + 1);
	return (buf);
}
