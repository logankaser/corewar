/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:04:31 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/22 12:05:00 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

int		check_screen(unsigned *pause)
{
	int x;
	int y;

	getmaxyx(stdscr, y, x);
	if (y < 65 | x < 222)
	{
		mvprintw(y / 2, x / 2 - 13, "Please increase screen size");
		*pause = 1;
		return (1);
	}
	return (0);
}
