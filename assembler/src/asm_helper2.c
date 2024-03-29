/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helper2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:45:31 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/07 14:07:47 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		asm_error(char *er_name, char *er_type, int line)
{
	ft_fprintf(stderr,
		RED_TEXT"%s: %s [line %d]\n"COLOR_RESET, er_name, er_type, line);
	exit(1);
}

void		ft_uvector_reset(t_uvector *vector, int size)
{
	free(vector->data);
	ft_uvector_init(vector, size);
	vector->data[0] = '\0';
}

void		asm_readline_str(t_asm *out, int fd, char **buf, t_uvector *in)
{
	while (asm_readline(out, fd, buf))
	{
		ft_string_append(in, *buf);
		ft_strdel(buf);
		if (valid_header_block(in, out))
			break ;
		if (!contains_non_comment((char*)in->data))
			ft_uvector_reset(in, 1);
		ft_string_append(in, "\n");
	}
}

char		*ft_strndup(char *str, int len)
{
	char *new;

	new = ft_strnew(len + 1);
	ft_strlcat(new, str, len + 1);
	return (new);
}

int			end_check(int fd)
{
	long size;
	char c;

	c = 0;
	if ((size = lseek(fd, -1, SEEK_END)) == -1)
		perror("lseek error");
	read(fd, &c, 1);
	if (c != '\n')
		return (0);
	return (1);
}
