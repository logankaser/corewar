/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:02:33 by jbeall            #+#    #+#             */
/*   Updated: 2019/05/22 12:05:13 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H
# include <ncurses.h>

typedef struct s_vm	t_vm;

void	init_visual(void);
void	render_vbar(int y);
void	write_mem(t_vm *vm);
bool	check_screen(bool *pause);
void	render_pc(t_vm *vm);
void	render(t_vm *vm);

#endif
