/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 13:43:24 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/11 13:46:17 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_min(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

double	ft_max(double a, double b)
{
	if (a < b)
		return (b);
	return (a);
}
