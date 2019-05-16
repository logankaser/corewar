/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:15:34 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/07 14:05:17 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

# define COLOR_RESET	"\033[0m"
# define BOLD			"\033[1m"
# define BLACK_TEXT		"\033[30;1m"
# define RED_TEXT		"\033[31;1m"
# define GREEN_TEXT		"\033[32;1m"
# define YELLOW_TEXT	"\033[33;1m"
# define BLUE_TEXT		"\033[34;1m"
# define MAGENTA_TEXT	"\033[35;1m"
# define CYAN_TEXT		"\033[36;1m"
# define WHITE_TEXT		"\033[37;1m"

# define CAPTURE_BUFF COMMENT_LENGTH
# define LABEL_MAP(x) &(x->label_map)
# define NUM_CHARS "-0123456789"

typedef struct	s_asm
{
	t_header	*header;
	uint8_t		program[CHAMP_MAX_SIZE];
	t_map		label_map;
	int			num_label;
	t_uvector	cmd_vec;
	unsigned	mem_ptr;
	int			line;
}				t_asm;

typedef struct	s_label
{
	char		*label_name;
	int			label_id;
	unsigned	mem_addr;
}				t_label;

typedef struct	s_asm_arg
{
	int			type;
	int			byte_size;
	int			use_label;
	char		*label_name;
	int			val;
}				t_asm_arg;

typedef struct	s_asm_cmd
{
	uint8_t		op_code;
	char		*name;
	uint8_t		encode;
	uint8_t		has_encode;
	unsigned	mem_addr;
	unsigned	num_args;
	t_uvector	args;
}				t_asm_cmd;

/*
** helpers
*/
int				ft_isspace(int c);
char			*skip_space(char *in);
char			*skip_comment(char *in);
int				asm_readline(t_asm *out, int fd, char **buf);
void			asm_error(char *er_name, char *er_type, int line);
void			ft_uvector_reset(t_uvector *vector, int size);
void			asm_readline_str(t_asm *out, int fd, char **buf, t_uvector *in);
char			*ft_strndup(char *str, int len);
int				end_check(int fd);

/*
** parse_header
*/
int				capture_header_field(char *in, t_asm *out, char *field,
	size_t len);
int				contains_non_comment(char *st);
int				valid_header_block(t_uvector *block, t_asm *out);
char			*capture_to_space(char *in);
char			*capture_to_quote(char *in);

/*
** parse_command
*/
uint32_t		valid_cmd_name(t_asm_cmd *cmd, t_asm *out);
int				valid_cmd_nb_args(t_asm_cmd *cmd, t_asm *out);
int				valid_arg_type(t_asm_cmd *cmd, t_asm *out, int j);
int				valid_cmd(t_asm_cmd *cmd, t_asm *out);
char			*parse_cmd_inner(char *line, t_asm *out, t_asm_cmd *new);
char			*parse_cmd(char *line, t_asm *out);
int				calc_cmd_size(t_asm_cmd *cmd);
uint8_t			encode_byte(t_asm_cmd *cmd);
void			deref_labels(t_asm *out);

/*
** parse_arg
*/
char			*parse_arg_lab(char *line);
char			*parse_arg_set_label(t_asm_arg *new, char *line);
char			*parse_arg_set_direct(t_asm_arg *new, char *line);
char			*parse_arg_val(char *line, t_asm_arg *new);
char			*parse_arg(char *line, t_asm *out, t_asm_cmd *cmd);

/*
** error
*/
void			asm_error(char *er_name, char *er_type, int line);
void			check_file_type(char *str);

/*
** write_validate
*/
int				validate_label(char *label, int len, t_asm *out);
char			*parse_arg_reg(char *line, t_asm *out, t_asm_arg *new);
unsigned		write_arg_data(t_asm *out, t_asm_arg *arg, unsigned ptr);
void			write_cmd_data(t_asm *out);

/*
** print
*/
void			asm_print_arg(t_asm_arg *arg);
void			asm_print_cmd(t_asm_cmd *cmd);
void			asm_print_data(t_asm *data);
void			create_file(t_asm *out, char *str);
char			*get_name(char *str);

#endif
