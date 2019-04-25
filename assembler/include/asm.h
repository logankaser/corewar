/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:15:34 by jbeall            #+#    #+#             */
/*   Updated: 2019/04/25 10:06:28 by jbeall           ###   ########.fr       */
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

#endif