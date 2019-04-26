/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:15:34 by jbeall            #+#    #+#             */
/*   Updated: 2019/04/26 10:19:53 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "libft.h"
#include "op.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define CAPTURE_BUFF COMMENT_LENGTH
#define LABEL_MAP(x) &(x->label_map)

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
	int val;
}				t_asm_arg;

typedef struct s_asm_cmd
{
	int op_code;
	char *name;
	int mem_addr;
	int num_args;
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
** error
*/
void asm_error(char *er_name, char *er_type, int line);

#endif