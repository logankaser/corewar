/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:21:13 by tcherret          #+#    #+#             */
/*   Updated: 2019/04/28 17:27:08 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_file_type(char *str)
{
	int size;

	size = ft_strlen(str);
	if (str[size - 1] != 's' || str[size - 2] != '.')
		asm_error("file error", "file must be '.s'", 0);
}

int		create_file(t_asm *out, char *str)
{
	char	*name;
	int		fd;

	name = ft_strf("%s.cor", str);
	if ((fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		asm_error("file error", "impossible to create the .cor file", 0);
	write(fd, out->header, sizeof(t_header));
	write(fd, out->program, ft_byteswap4(out->header->prog_size));
	close(fd);
	ft_printf(GREEN_TEXT "Writing .cor file to /%s!\n" COLOR_RESET, name);
	free(name);
	return (0);
}
