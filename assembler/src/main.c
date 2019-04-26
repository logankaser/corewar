/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:28:10 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/26 13:38:57 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void asm_error(char *er_name, char *er_type, int line)
{
	ft_printf("%s: %s [line %d]\n", er_name, er_type, line);
	exit(0);
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
		while (asm_readline(out, fd, &buf))
		{
			ft_string_append(&in, buf);
			ft_strdel(&buf);
			if (valid_header_block(&in, out))
				break;
			ft_string_append(&in, "\n");
		}
		if(!name_flag && (name_flag = capture_header_field((char*)in.data, out, NAME_CMD_STRING, PROG_NAME_LENGTH)))
			ft_uvector_reset(&in, 1);
		else if (!comment_flag && (comment_flag = capture_header_field((char*)in.data, out, COMMENT_CMD_STRING, COMMENT_LENGTH)))
			ft_uvector_reset(&in, 1);
		else
			asm_error("error", "incomplete header", out->line);
	}
	return (0);
}

int validate_label(char *label, int len, t_asm *out)
{
	char *name;
	t_label *new;

	name = ft_strnew(len);
	ft_strncpy(name, label, len);;
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
	int i;
	char *tmp;

	new->type = T_REG;
	new->byte_size = 1;
	i = 0;
	while(line[i] >= '0' & line[i] <= '9')
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
	int i;
	char *tmp;

	i = 0;
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		i++;
	tmp = ft_strndup(line, i);
	return (tmp);
}

char *parse_arg_val(char *line, t_asm_arg *new)
{
	int i;
	char *tmp;

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
		while(line[i] >= '0' & line[i] <= '9')
			i++;
		tmp = ft_strndup(line, i);
		new->val = ft_atoi(tmp);
		//validate conversion
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
	else if (*line == DIRECT_CHAR || ft_strchr(NUM_CHARS, *line) || *line == LABEL_CHAR)
		line = parse_arg_val(line, new);
	ft_uvector_push(&(cmd->args), new);
	return (line);
}

char *parse_cmd(char *line, t_asm *out)
{
	char *cmd_name;
	t_asm_cmd *new;
	int len;

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
		if (*line == COMMENT_CHAR)
			break;
		if (new->num_args && *line++ != SEPARATOR_CHAR)
			asm_error("syntax error", "no separator char", out->line);
		line = skip_space(line);
		line = parse_arg(line, out, new);
		++new->num_args;
	}
	//validate cmd
	//update mem_ptr
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
	if (*line && *line != COMMENT_CHAR)
		line  = parse_cmd(line, out);
	line = skip_space(line);
	if (*line && *line != COMMENT_CHAR)
		asm_error("syntax error", "invalid command block", out->line);
}

void parse_body(int fd, t_asm *out)
{
	char *buf;

	while (asm_readline(out, fd, &buf))
	{
		parse_line(buf, out);
		ft_strdel(&buf);
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
	//write size to header
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
	asm_print_data(&out);
	return (0);
}
