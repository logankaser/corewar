/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:28:10 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/24 21:27:47 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	else
		return (0);
}

char *skip_space(char *in)
{
	while (ft_isspace(*in))
		in++;
	return (in);
}

char *skip_comment(char *in)
{
	while (*in != '\n')
		in++;
	return in++;
}

char *capture_to_space(char *in)
{
	int len;
	static char buf[CAPTURE_BUFF];

	len = 0;
	ft_bzero(buf, CAPTURE_BUFF);
	while (in[len] && len < CAPTURE_BUFF - 1 && !ft_isspace(in[len]))
		len++;
	ft_strlcat(buf, in, CAPTURE_BUFF);
	return buf;
}

char *capture_to_quote(char *in)
{
	int len;
	static char buf[CAPTURE_BUFF];

	len = 0;
	ft_bzero(buf, CAPTURE_BUFF);
	while (in[len] && len < CAPTURE_BUFF - 1 && in[len] != '"')
		len++;
	ft_strlcat(buf, in, len + 1);
	return buf;
}

int capture_header_field(char *in, t_header *header, char *field, size_t len)
{
	char *val;
	in = skip_space(in);
	if (!ft_strncmp(in, field, ft_strlen(field)))
	{
		in += ft_strlen(field);
		in = skip_space(in);
		if (*in == '"')
		{
			if(!(val = capture_to_quote(++in)))
				ft_exit("syntax error: no end quote", 1);
			if (ft_strlen(val) > len)
				ft_exit("error: val exceeds length", 1);
			if (!ft_strcmp(field, NAME_CMD_STRING))
				ft_strlcat(header->prog_name, val, len);
			else if (!ft_strcmp(field, COMMENT_CMD_STRING))
				ft_strlcat(header->comment, val, len);
		}
		else
			ft_exit("sytax error: bad character", 2);
	}
	else
		return (0);
	return (1);
}

int contains_non_comment(char *st)
{
	st = skip_space(st);
	if (*st && *st != '#')
		return (1);
	return (0);
}

int valid_header_block(t_uvector *block)
{
	int quote;
	unsigned i;

	quote = 0;
	i = 0;
	while (i < block->length && quote < 2)
	{
		if (block->data[i] == '"')
			quote++;
		i++;
	}
	if (quote == 2 && contains_non_comment((char*)(block->data + i)))
		ft_exit("syntax error: bad character", 1);
	if (quote == 2)
		return (1);
	return (0);
}

void ft_uvector_reset(t_uvector *vector, int size)
{
	free(vector->data);
	ft_uvector_init(vector, size);
	vector->data[0] = '\0';
}

int parse_header(int fd, t_asm *out)
{
	int name_flag;
	int comment_flag;
	char *buf;
	t_uvector in;

	name_flag = 0;
	comment_flag = 0;
	out->header = ft_memalloc(sizeof(t_header));
	ft_uvector_init(&in, 1);
	in.data[0] = '\0';
	while (!(name_flag && comment_flag))
	{
		while (get_next_line(fd, &buf))
		{
			ft_string_append(&in, buf);
			ft_strdel(&buf);
			if (valid_header_block(&in))
				break;
			ft_string_append(&in, "\n");
		}
		if(!name_flag && (name_flag = capture_header_field((char*)in.data, out->header, NAME_CMD_STRING, PROG_NAME_LENGTH)))
			ft_uvector_reset(&in, 1);
		else if (!comment_flag && (comment_flag = capture_header_field((char*)in.data, out->header, COMMENT_CMD_STRING, COMMENT_LENGTH)))
			ft_uvector_reset(&in, 1);
		else
			ft_exit("error: incomplete header", 1);
	}
	return (0);
}

unsigned reverse_endian(unsigned in)
{
	unsigned out;

	out = in >> 3 * 8;
	out += (in & (0xff << 2 * 8)) >> 1 * 8;
	out += (in & (0xff << 1 * 8)) << 1 * 8;
	out += (in & (0xff << 0 * 8)) << 3 * 8;
	return (out);
}

void parse(int fd, t_asm *out)
{
	parse_header(fd, out);
	out->header->magic = reverse_endian(COREWAR_EXEC_MAGIC);
	write(1, out->header, sizeof(t_header));
}

int main(int argc, char **argv)
{
	int fd;
	t_asm out;

	if (argc != 2)
	{
		ft_printf("Usage: asm <sourcefile.s>\n");
		return (0);
	}
	ft_bzero(&out, sizeof(out));
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		perror("error");
		return(0);
	}
	parse(fd, &out);
	return (0);
}
