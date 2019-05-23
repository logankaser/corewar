/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:40:49 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/22 13:11:15 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
#include "visual.h"
#define INFO_X 194

void		init_visual(void)
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, true);
	start_color();
	use_default_colors();
	init_color(-1, 700, 700, 700);
	init_color(COLOR_CYAN, 400, 400, 400);
	init_pair(1, -1, -1);
	init_pair(2, COLOR_CYAN, -1);
	init_pair(3, COLOR_GREEN, -1);
	init_pair(4, COLOR_BLUE, -1);
	init_pair(5, COLOR_RED, -1);
	init_pair(6, COLOR_YELLOW, -1);
	curs_set(0);
}

static void	render_player_info(t_vm *vm)
{
	unsigned	i;
	static int	color_p[] = {0, 3, 4, 5, 6};

	i = 0;
	while (i < vm->player_count)
	{
		move(9 + (4 * i), INFO_X);
		printw("Player ");
		attron(COLOR_PAIR(color_p[i + 1]) | A_STANDOUT);
		printw("%d\n", i + 1);
		attroff(COLOR_PAIR(color_p[i + 1]) | A_STANDOUT);
		move(10 + 4 * i, INFO_X);
		printw("Last Live Cycle: %d", vm->players[i]->last_live_cycle);
		i++;
	}
}

static void	render_info(t_vm *vm, unsigned speed, bool pause)
{
	render_vbar(192);
	attron(A_BOLD);
	if (pause)
		mvprintw(1, INFO_X, "Paused");
	else
		mvprintw(1, INFO_X, "Speed: %d", speed);
	mvprintw(3, INFO_X, "Cycle: %d", vm->cycle);
	mvprintw(5, INFO_X, "Player Count: %d", vm->player_count);
	mvprintw(7, INFO_X, "Processes: %d", vm->process_count);
	mvprintw(55, INFO_X, "Cycles To Die: %d", vm->cycles_to_die);
	mvprintw(57, INFO_X, "Live Checks: %d", vm->checks);
	mvprintw(59, INFO_X, "Next Check Cycle: %d", vm->check_cycle);
	mvprintw(61, INFO_X, "Cycle Delta: %d", CYCLE_DELTA);
	mvprintw(63, INFO_X, "Lives This Round: %d", vm->lives);
	render_player_info(vm);
	attroff(A_BOLD);
}

static void	get_input(unsigned *speed, bool *pause)
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

void		render(t_vm *vm)
{
	static unsigned	delay[] = {1000000, 100000, 10000, 1000, 100, 0};
	static unsigned	speed = 2;
	bool			loop;

	loop = true;
	while (loop)
	{
		erase();
		if (!check_screen(&vm->pause))
		{
			write_mem(vm);
			render_pc(vm);
			render_info(vm, speed, vm->pause);
		}
		refresh();
		get_input(&speed, &vm->pause);
		loop = vm->pause;
	}
	usleep(delay[speed]);
}
