/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:28:10 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/28 17:09:35 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void asm_error(char *er_name, char *er_type, int line)
{
	ft_printf(RED_TEXT"%s: %s [line %d]\n"COLOR_RESET, er_name, er_type, line);
	exit(0);
}

void ft_uvector_reset(t_uvector *vector, int size)
{
	free(vector->data);
	ft_uvector_init(vector, size);
	vector->data[0] = '\0';
}

void asm_readline_str(t_asm *out, int fd, char **buf, t_uvector *in)
{
	while (asm_readline(out, fd, buf))
	{
		ft_string_append(in, *buf);
		ft_strdel(buf);
		if (valid_header_block(in, out))
			break ;
		if (!contains_non_comment((char*)in->data))
			ft_uvector_reset(in, 1);
		ft_string_append(in, "\n");
	}
}

int parse_header(int fd, t_asm *out)
{
	int			name_flag;
	int			comment_flag;
	char		*buf;
	t_uvector	in;

	name_flag = 0;
	comment_flag = 0;
	out->header = ft_memalloc(sizeof(t_header));
	ft_uvector_init(&in, 1);
	in.data[0] = '\0';
	while (!(name_flag && comment_flag))
	{
		asm_readline_str(out, fd, &buf, &in);
		if (!name_flag && (name_flag = capture_header_field((char*)in.data, out,
			NAME_CMD_STRING, PROG_NAME_LENGTH)))
			ft_uvector_reset(&in, 1);
		else if (!comment_flag && (comment_flag = capture_header_field((char*)
			in.data, out, COMMENT_CMD_STRING, COMMENT_LENGTH)))
			ft_uvector_reset(&in, 1);
		else
			asm_error("error", "incomplete header", out->line);
	}
	return (0);
}

int validate_label(char *label, int len, t_asm *out)
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

char *parse_arg_reg(char *line, t_asm *out, t_asm_arg *new)
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

char *ft_strndup(char *str, int len)
{
	char *new;

	new = ft_strnew(len + 1);
	ft_strlcat(new, str, len + 1);
	return (new);
}

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

char *parse_arg_val(char *line, t_asm_arg *new)
{
	int		i;
	char	*tmp;

	i = 0;
	if (*line == DIRECT_CHAR)
	{
		line++;
		new->type = T_DIR;
		new->byte_size = 4;
	}
	else
	{
		new->type = T_IND;
		new->byte_size = 2;
	}
	if (*line == LABEL_CHAR)
	{
		new->use_label = 1;
		new->label_name = parse_arg_lab(++line);
		while (*line && ft_strchr(LABEL_CHARS, *line))
			line++;
	}
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

int calc_cmd_size(t_asm_cmd *cmd)
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

uint8_t encode_byte(t_asm_cmd *cmd)
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

char *parse_cmd(char *line, t_asm *out)
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
	valid_cmd(new, g_op_tab, out);
	new->encode = new->has_encode ? encode_byte(new) : 0;
	out->mem_ptr += calc_cmd_size(new);
	ft_uvector_push(&(out->cmd_vec), new);
	return (line);
}

void parse_line(char *line, t_asm *out)
{
	int has_label;
	int has_cmd;
	int i;

	i = 0;
	has_label = 0;
	has_cmd = 0;
	line = skip_space(line);
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		++i;
	if (line[i] == LABEL_CHAR)
		line += validate_label(line, i, out);
	line = skip_space(line);
	if (*line && *line != COMMENT_CHAR && *line != ';')
		line = parse_cmd(line, out);
	line = skip_space(line);
	if (*line && *line != COMMENT_CHAR && *line != ';')
		asm_error("syntax error", "invalid command block", out->line);
}

void deref_labels(t_asm *out)
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

void parse_body(int fd, t_asm *out)
{
	char *buf;

	while (asm_readline(out, fd, &buf))
	{
		parse_line(buf, out);
		ft_strdel(&buf);
	}
	deref_labels(out);
}

uint16_t reverse_endian_two(uint16_t val)
{
	uint16_t ret;

	ret = 0;
	ret = (val & 0xFF) << 8;
	ret += (val & (0xFF << 8)) >> 8;
	return (ret);
}

unsigned write_arg_data(t_asm *out, t_asm_arg *arg, unsigned ptr)
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

void write_cmd_data(t_asm *out)
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

/*
** Init vectors and launch parse operators
*/

void parse(int fd, t_asm *out)
{
	ft_map_init(&(out->label_map), 0, 17);
	ft_uvector_init(&(out->cmd_vec), sizeof(t_asm_cmd));
	parse_header(fd, out);
	out->header->magic = reverse_endian(COREWAR_EXEC_MAGIC);
	parse_body(fd, out);
	out->header->prog_size = reverse_endian(out->mem_ptr);
	if (reverse_endian(out->header->prog_size) > CHAMP_MAX_SIZE)
		asm_error("error", "champion exceeds max size", 0);
	write_cmd_data(out);
}

int main(int argc, char **argv)
{
	int		fd;
	t_asm	out;

	if (argc != 2)
	{
		ft_printf(RED_TEXT"Usage: asm <sourcefile.s>\n"COLOR_RESET);
		return (0);
	}
	ft_bzero(&out, sizeof(out));
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		perror("error");
		return (0);
	}
	check_file_type(argv[1]);
	parse(fd, &out);
	//asm_print_data(&out);
	create_file(&out, argv[1]);
	write(1, out.program, out.header->prog_size);
	return (0);
}
