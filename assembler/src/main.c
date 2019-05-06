/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:28:10 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/28 21:18:37 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		parse_header(int fd, t_asm *out)
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

void	parse_line(char *line, t_asm *out)
{
	int i;

	i = 0;
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

void	parse_body(int fd, t_asm *out)
{
	char *buf;

	while (asm_readline(out, fd, &buf))
	{
		parse_line(buf, out);
		ft_strdel(&buf);
	}
	deref_labels(out);
}

/*
** Init vectors and launch parse operators
*/

void	parse(int fd, t_asm *out)
{
	ft_map_init(&(out->label_map), 0, 17);
	ft_uvector_init(&(out->cmd_vec), sizeof(t_asm_cmd));
	parse_header(fd, out);
	out->header->magic = ft_byteswap4(COREWAR_EXEC_MAGIC);
	parse_body(fd, out);
	out->header->prog_size = ft_byteswap4(out->mem_ptr);
	if (ft_byteswap4(out->header->prog_size) > CHAMP_MAX_SIZE)
		asm_error("error", "champion exceeds max size", 0);
	write_cmd_data(out);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		debug;
	t_asm	out;

	debug = 0;
	if (argc == 3 && ft_strcmp(argv[1], "-d") == 0)
		debug = 1;
	if ((argc < 2 && argc > 3) || (argc == 3 && ft_strcmp(argv[1], "-d") != 0))
	{
		ft_printf(RED_TEXT"Usage: asm -d <sourcefile.s>\n"COLOR_RESET);
		return (0);
	}
	ft_bzero(&out, sizeof(out));
	if ((fd = open(argv[argc - 1], O_RDONLY)) < 0)
	{
		perror("error");
		return (0);
	}
	check_file_type(argv[argc - 1]);
	parse(fd, &out);
	if (debug == 1)
		asm_print_data(&out);
	create_file(&out, argv[argc - 1]);
	return (0);
}
