/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 11:31:14 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/22 12:12:57 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "virtual_machine.h"

void		render_vbar(int y)
{
	int i;

	i = 0;
	while (i < 64)
	{
		move(i, y);
		printw("|");
		i++;
	}
}

static void	write_hex(t_vm *vm, int i)
{
	move(i / 64, (i % 64) * 3);
	printw("%02x", vm->arena[i]);
}

void		write_mem(t_vm *vm)
{
	int i;
	int j;

	i = 0;
	j = 0;
	attron(COLOR_PAIR(1));
	while (i < MEM_SIZE / 64)
	{
		j = 0;
		while (j < 64)
		{
			if (!vm->arena[i * 64 + j])
				attron(COLOR_PAIR(2));
			write_hex(vm, i * 64 + j);
			attron(COLOR_PAIR(1));
			j++;
		}
		printw("\n");
		i++;
	}
	attroff(COLOR_PAIR(1));
}

bool		check_screen(bool *pause)
{
	int x;
	int y;

	getmaxyx(stdscr, y, x);
	if (y < 65 | x < 222)
	{
		mvprintw(y / 2, x / 2 - 13, "Please increase screen size");
		*pause = 1;
		return (true);
	}
	return (false);
}

void		render_pc(t_vm *vm)
{
	t_process	*proc;
	static int	color_p[] = {0, 3, 4, 5, 6};

	proc = vm->processes;
	attron(A_BOLD | A_STANDOUT);
	while (proc)
	{
		attron(COLOR_PAIR(color_p[-proc->owner]));
		write_hex(vm, proc->pc % MEM_SIZE);
		attroff(COLOR_PAIR(color_p[-proc->owner]));
		proc = proc->next;
	}
	attroff(A_BOLD | A_STANDOUT);
}
