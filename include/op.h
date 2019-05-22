/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:42:00 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/01 17:01:50 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include <stdint.h>
# include <stdbool.h>

# define IND_SIZE 2
# define REG_SIZE 4
# define DIR_SIZE REG_SIZE

# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3

# define MAX_ARGS_NUMBER 4
# define MAX_PLAYERS 4
# define MEM_SIZE (4 * 1024)
# define IDX_MOD (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE (MEM_SIZE / 6)

# define COMMENT_CHAR '#'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','

# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING ".name"
# define COMMENT_CMD_STRING ".comment"

# define REG_NUMBER 16

# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA 50
# define NBR_LIVE 21
# define MAX_CHECKS 10

/*
** Arg.
*/

typedef char	t_arg_type;

# define T_REG 1
# define T_DIR 2
# define T_IND 4
# define T_LAB 8

/*
** Filetype.
*/

# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3
# define HEADER_SIZE (16 + PROG_NAME_LENGTH + COMMENT_LENGTH)

typedef struct	s_header
{
	unsigned	magic;
	char		prog_name[PROG_NAME_LENGTH + 1];
	unsigned	prog_size;
	char		comment[COMMENT_LENGTH + 1];
}				t_header;

typedef struct	s_op
{
	const char	*name;
	uint8_t		param_num;
	t_arg_type	param_types[MAX_ARGS_NUMBER];
	uint8_t		opcode;
	uint32_t	cycles;
	const char	*description;
	bool		encoded;
	bool		halfwidth;
}				t_op;

extern t_op			const g_op_tab[17];

#endif
