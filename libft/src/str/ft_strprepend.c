/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprepend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:26:44 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:26:46 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strprepend(char const *add, char **str)
{
	char		*new;
	unsigned	len;
	unsigned	i;
	unsigned	j;

	len = (*str ? ft_strlen(*str) : 0) + (add ? ft_strlen(add) : 0);
	if ((new = malloc(len + 1)))
	{
		i = 0;
		if (add)
			while (*add)
				new[i++] = *add++;
		j = 0;
		if (str && *str)
			while ((*str)[j])
			{
				new[i + j] = (*str)[j];
				++j;
			}
		new[i + j] = '\0';
		free(*str);
		*str = new;
	}
}
