/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:06:27 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/01 17:06:28 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECODE_H
# define DECODE_H
# include <stdint.h>
# include <stdbool.h>
# include "op.h"
# include "virtual_machine.h"

# define P1(byte) ((byte & 0b11000000) >> 6)
# define P2(byte) ((byte & 0b00110000) >> 4)
# define P3(byte) ((byte & 0b00001100) >> 2)

/*
** Get parameter type of parameter x, parameters are 1 indexed.
*/
# define PX(byte, X) ((byte & (192 >> (((X) - 1) * 2))) >> (8 - ((X) * 2)))

# define REG 0b01
# define DIR 0b10
# define IND 0b11

/*
** total_width is the total width of the instruction,
** including opcode, encoding byte (if it has one), and paramaters.
*/

typedef struct	s_decode
{
	int32_t		values[4];
	uint8_t		offsets[4];
	uint8_t		types[4];
	uint8_t		direct_width;
}				t_decode;

int32_t			arena_load(uint8_t *arena, unsigned from, unsigned size);
void			arena_store(uint8_t *arena, unsigned at, int32_t value,
	unsigned size);

unsigned		decode(t_decode *d, const t_op *op, uint8_t enc);

bool			decode_load(t_decode *d, const t_op *op, uint8_t *arena,
	t_process *p);
int32_t			param_read(t_decode *d, uint8_t *arena, t_process *p,
	unsigned n);

#endif
