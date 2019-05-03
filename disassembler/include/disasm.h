/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:27:12 by tcherret          #+#    #+#             */
/*   Updated: 2019/05/03 13:44:24 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H

#include "libft.h"
#include "op.h"
#include "../../virtual_machine/include/virtual_machine.h"
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

typedef struct s_disasm
{
	t_header	header;
	uint8_t		program[CHAMP_MAX_SIZE];
	unsigned	index;
	int			fdc;
}				t_disasm;

void			write_header(t_disasm *file_data);
unsigned		write_program_op(uint8_t op, t_op *g_op_tab, 
		t_disasm *file_data);
unsigned		write_live_zjmp_fork(uint8_t op, t_disasm *file_data);
unsigned		write_program(t_disasm *file_data, t_op *g_op_tab);
unsigned		write_param(unsigned type, uint8_t op, t_op *g_op_tab,
		t_disasm *file_data);
bool			validate_types(uint8_t *arena, unsigned pc);
bool			read_file(const char *filepath, t_uvector *buf);


#endif
