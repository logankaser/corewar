/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:15:34 by jbeall            #+#    #+#             */
/*   Updated: 2019/04/26 16:53:12 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "libft.h"
#include "op.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

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

#define CAPTURE_BUFF COMMENT_LENGTH
#define LABEL_MAP(x) &(x->label_map)
#define NUM_CHARS "-0123456789"

typedef struct s_asm
{
	t_header *header;
	uint8_t program[CHAMP_MAX_SIZE];
	t_map label_map;
	int num_label;
	t_uvector cmd_vec;
	unsigned mem_ptr;
	int line;
}				t_asm;

typedef struct s_label
{
	char *label_name;
	int label_id;
	unsigned mem_addr;
}				t_label;

typedef struct s_asm_arg
{
	int type;
	int byte_size;
	int use_label;
	char *label_name;
	int val;
}				t_asm_arg;

typedef struct s_asm_cmd
{
	int op_code;
	char *name;
	int encode;
	int mem_addr;
	unsigned num_args;
	t_uvector args;
}				t_asm_cmd;

/*
** helpers
*/
int	ft_isspace(int c);
char *skip_space(char *in);
char *skip_comment(char *in);
unsigned reverse_endian(unsigned in);
int asm_readline(t_asm *out, int fd, char **buf);

/*
** parse_header
*/
int capture_header_field(char *in, t_asm *out, char *field, size_t len);
int contains_non_comment(char *st);
int valid_header_block(t_uvector *block, t_asm *out);
char *capture_to_space(char *in);
char *capture_to_quote(char *in);

/*
** parse_command
*/

uint32_t	valid_cmd_name(t_asm_cmd *cmd, t_op *g_op_tab, t_asm *out);
int		valid_cmd_nb_args(t_asm_cmd *cmd, t_op *g_op_tab, t_asm *out);
int		valid_arg_type(t_asm_cmd *cmd, t_op *g_op_tab, t_asm *out, int j);
int		valid_cmd(t_asm_cmd *cmd, t_op *g_op_tab, t_asm *out);

/*
** error
*/
void asm_error(char *er_name, char *er_type, int line);
void	check_file_type(char *str);

/*
** print
*/
void asm_print_arg(t_asm_arg *arg);
void asm_print_cmd(t_asm_cmd *cmd);
void asm_print_data(t_asm *data);

#endif
