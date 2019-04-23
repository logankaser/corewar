/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:24:46 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:24:47 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strappend(char **str, char const *add)
{
	char		*new;
	unsigned	len;
	unsigned	i;
	unsigned	j;

	len = (*str ? ft_strlen(*str) : 0) + (add ? ft_strlen(add) : 0);
	if ((new = malloc(len + 1)))
	{
		i = 0;
		if (str && *str)
			while ((*str)[i])
			{
				new[i] = (*str)[i];
				++i;
			}
		j = 0;
		if (add)
			while (*add)
				new[i + j++] = *add++;
		new[i + j] = '\0';
		free(*str);
		*str = new;
	}
}
