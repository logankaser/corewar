/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <tcherret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:21:13 by tcherret          #+#    #+#             */
/*   Updated: 2019/04/26 20:30:00 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_file_type(char *str)
{
	int size;

	size = ft_strlen(str);
	if (str[size - 1] != 's' || str[size - 2] != '.')
		asm_error("file error", "file must be '.s'", 0);
	return (1);
}

char	*get_name(char *str)
{
	char *new;
	int size;
	int i;

	i = -1;
	size = ft_strlen(str);
	if (!(new = malloc(sizeof(char) * (size + 3))))
		return (NULL);
	while (++i != size - 2)
		new[i] = str[i];
	new[i] = '\0';
	new = ft_strcat(new, ".cor");
	return (new);
}

int		create_file(t_asm *out, char *str)
{
	char	*name;
	int		fd;

	name = get_name(str);
	if ((fd = open(name, O_CREAT, 0644)) < 0)
		asm_error("file error", "impossible to create the .cor file", 0);
	write(fd, out->header, sizeof(out->header));
	write(fd, out->program, sizeof(out->program));
	close(fd);
	ft_printf(GREEN_TEXT "The file %s was created!\n" COLOR_RESET, name);
	free(name);
	return (0);
}
