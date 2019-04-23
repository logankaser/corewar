/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:24:14 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:24:15 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		render_nbr(int nb, int fd)
{
	if (nb >= 10 || nb <= -10)
	{
		render_nbr(nb / 10, fd);
		render_nbr(nb % 10, fd);
	}
	else
		ft_putchar_fd((nb > 0 ? nb : nb * -1) + 48, fd);
}

void			ft_putnbr_fd(int nb, int fd)
{
	if (nb < 0)
		ft_putchar_fd('-', fd);
	render_nbr(nb, fd);
}
