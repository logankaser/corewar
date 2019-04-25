/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:15:34 by jbeall            #+#    #+#             */
/*   Updated: 2019/04/25 10:50:08 by jbeall           ###   ########.fr       */
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

typedef struct s_asm
{
	t_header *header;
	uint8_t program[CHAMP_MAX_SIZE];
	int line;
}				t_asm;

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