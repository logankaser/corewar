/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:40:49 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/21 13:18:01 by jbeall           ###   ########.fr       */
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
