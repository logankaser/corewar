/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:43:58 by jbeall            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/04/25 14:55:44 by jbeall           ###   ########.fr       */
=======
/*   Updated: 2019/04/25 10:46:19 by jbeall           ###   ########.fr       */
>>>>>>> d63eafbe29a298e81ad28cff8791652640504f65
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	else
		return (0);
}

char *skip_space(char *in)
{
	while (ft_isspace(*in))
		in++;
	return (in);
}

char *skip_comment(char *in)
{
	while (*in != '\n')
		in++;
	return in++;
}

<<<<<<< HEAD
uint32_t reverse_endian(uint32_t in)
=======
unsigned reverse_endian(unsigned in)
>>>>>>> d63eafbe29a298e81ad28cff8791652640504f65
{
	unsigned out;

	out = in >> 3 * 8;
	out += (in & (0xff << 2 * 8)) >> 1 * 8;
	out += (in & (0xff << 1 * 8)) << 1 * 8;
	out += (in & (0xff << 0 * 8)) << 3 * 8;
	return (out);
}

int asm_readline(t_asm *out, int fd, char **buf)
{
	int ret = get_next_line(fd, buf);
	if (ret)
		out->line += 1;
	return (ret);
}
