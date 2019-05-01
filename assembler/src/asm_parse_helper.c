/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:43:58 by jbeall            #+#    #+#             */
/*   Updated: 2019/04/28 16:01:48 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	else
		return (0);
}

char		*skip_space(char *in)
{
	while (ft_isspace(*in))
		in++;
	return (in);
}

char		*skip_comment(char *in)
{
	while (*in != '\n')
		in++;
	return (in++);
}

int			asm_readline(t_asm *out, int fd, char **buf)
{
	int ret;

	ret = get_next_line(fd, buf);
	if (ret)
		out->line += 1;
	return (ret);
}
