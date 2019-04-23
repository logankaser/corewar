/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:23:59 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:24:00 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puterror(char const *error)
{
	write(2, error, *error ? ft_strlen(error) : 0);
	write(2, "\n", 1);
}

void	ft_exit(char const *error, int code)
{
	write(2, error, *error ? ft_strlen(error) : 0);
	write(2, "\n", 1);
	exit(code);
}
