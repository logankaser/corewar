/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:40:49 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/21 11:23:40 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
#include "visual.h"

void init_visual(void)
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, true);
	start_color();
	init_color(COLOR_WHITE, 700, 700, 700);
	init_color(10, 400, 400, 400);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, 10, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	curs_set(0);
}

void write_hex(t_vm *vm, int i)
{
	move(i / 64, (i % 64) * 3);
	printw("%02x", vm->arena[i]);
}

void write_mem(t_vm *vm)
{
	int i;
	int j;

	i = 0;
	j = 0;
	move(0, 0);
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

void render_pc(t_vm *vm)
{
	t_process *proc;
	int color_p[] = {0, 3, 4, 5, 6};

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

int count_processes(t_vm *vm)
{
	t_process *p;
	int count;

	p = vm->processes;
	count = 0;
	while (p)
	{
		count++;
		p = p->next;
	}
	return (count);
}

void render_vbar(int y)
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

void render_player_info(t_vm *vm)
{
	unsigned i;
	int color_p[] = {0, 3, 4, 5, 6};

	i = 0;
	while (i < vm->player_count)
	{
		move(9 + (4 * i), 200);
		printw("Player ");
		attron(COLOR_PAIR(color_p[i + 1]) | A_STANDOUT);
		printw("%d\n", i + 1);
		attroff(COLOR_PAIR(color_p[i + 1]) | A_STANDOUT);
		move(10 + 4 * i, 200);
		printw("Last Live Cycle: %d", vm->players[i]->last_live_cycle);
		i++;
	}
}

void render_info(t_vm *vm, unsigned speed, unsigned pause)
{
	render_vbar(197);
	attron(A_BOLD);
	if (pause)
		mvprintw(1, 200, "Paused");
	else
		mvprintw(1, 200, "Speed: %d", speed);
	mvprintw(3, 200, "Cycle: %d", vm->cycle);
	mvprintw(5, 200, "Player Count: %d", vm->player_count);
	mvprintw(7, 200, "Processes: %d", count_processes(vm));
	mvprintw(55, 200, "Cycles To Die: %d", vm->cycles_to_die);
	mvprintw(57, 200, "Live Checks: %d", vm->checks);
	mvprintw(59, 200, "Next Check Cycle: %d", vm->check_cycle);
	mvprintw(61, 200, "Cycle Delta: %d", CYCLE_DELTA);
	mvprintw(63, 200, "Lives This Round: %d", vm->lives);
	render_player_info(vm);
	attroff(A_BOLD);
}

void get_input(unsigned *speed, unsigned *pause)
{
	char in;

	in = getch();
	if (in == ' ')
		*pause = *pause ? 0 : 1;
	if (in == '=')
		*speed = *speed < 5 ? *speed + 1 : *speed;
	if (in == '-')
		*speed = *speed > 0 ? *speed - 1 : *speed;
	if (in == 'q')
	{
		endwin();
		exit(1);
	}
}

void render(t_vm *vm)
{
	int line;
	static unsigned delay[] = {1000000, 100000, 10000, 1000, 100, 0};
	static unsigned speed = 2;
	unsigned pause;

	line = 0;
	pause = 0;
	do {
		erase();
		write_mem(vm);
		render_pc(vm);
		render_info(vm, speed, pause);
		refresh();
		get_input(&speed, &pause);
	} while (pause);
	usleep(delay[speed]);
}