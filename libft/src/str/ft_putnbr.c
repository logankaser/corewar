/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:24:10 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:24:11 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		render_nbr(int nb)
{
	if (nb >= 10 || nb <= -10)
	{
		render_nbr(nb / 10);
		render_nbr(nb % 10);
	}
	else
		ft_putchar((nb > 0 ? nb : nb * -1) + '0');
}

void			ft_putnbr(int nb)
{
	if (nb < 0)
		ft_putchar('-');
	render_nbr(nb);
}
