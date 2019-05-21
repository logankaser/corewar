/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:03:28 by lkaser            #+#    #+#             */
/*   Updated: 2019/05/05 15:14:10 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "virtual_machine.h"
#include "instruction_dispatch.h"
#include "process.h"

void					vm_init(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->dump_cycle = UINT_MAX;
}

void					vm_del(t_vm *vm)
{
	unsigned	i;
	t_process	*proc;
	t_process	*tmp;

	i = 0;
	while (i < vm->player_count)
		free(vm->players[i++]);
	proc = vm->processes;
	while (proc)
	{
		tmp = proc;
		proc = proc->next;
		free(tmp);
	}
}

/*
# define DUMP_LEN 64

static void		build_dump(char *out, uint8_t *arena, int addrlen)
{
	size_t	line;
	size_t	i;

	i = 0;
	line = 0;
	out += sprintf(out, "0x%.*x : ", addrlen, 0);
	while (i < MEM_SIZE)
	{
		if (++line == DUMP_LEN)
		{
			line = 0;
			out += sprintf(out, "%.2x \n", arena[i++]);
			if (i < MEM_SIZE)
				out += sprintf(out, "%#.*zx : ", addrlen, i);
			continue ;
		}
		out += sprintf(out, "%.2x ", arena[i++]);
	}
}

static size_t	dumplen(int *addrlen)
{
	int	msize;
	int	alen;

	alen = 0;
	if (!(msize = MEM_SIZE))
		alen = 1;
	while (msize)
	{
		++alen;
		msize /= 16;
	}
	*addrlen = alen;
	return (((MEM_SIZE / DUMP_LEN) * (alen + 6)) + (MEM_SIZE * 3));
}

void			dump(t_vm *vm)
{
	char	*out;
	size_t	olen;
	char	*sep;
	int		slen;
	int		addrlen;
	t_process *p;

	olen = dumplen(&addrlen);
	slen = (DUMP_LEN * 3) + addrlen + 4;
	out = malloc(olen + 1);
	sep = malloc(slen + 1);
	sep[slen] = '\0';
	ft_memset(sep, '-', slen);
	build_dump(out, vm->arena, addrlen);
	ft_printf("%s\nCORE DUMP [CYCLE %u]\n%s\n", sep, --vm->cycle, sep);
	write(STDOUT_FILENO, out, olen);
	free(out);
	free(sep);

	p = vm->processes;
	while (p)
	{
		printf("P%4u:%u = %s:%u\n",
			p->id,
			p->pc,
			p->executing == NONE ? "NONE" : g_op_tab[p->executing - 1].name,
			p->execute_cycle
		);
		for (int i = 0; i < 16; ++i)
		{
			printf("r%.2i = %.8x \n", i + 1, p->registers[i]);
		}
		p = p->next;
	}

	exit(EXIT_SUCCESS);
}
*/

void					vm_run(t_vm *vm)
{
	t_process	*proc;
	t_decode	d;

	while (vm->processes)
	{
		if (++vm->cycle > vm->dump_cycle)
		{
			//dump(vm);
			break ;
		}
		proc = vm->processes;
		while(proc)
		{
			if (vm->cycle < proc->execute_cycle)
			{
				proc = proc->next;
				continue ;
			}
			if (proc->executing != NONE)
			{
				uint8_t opi = proc->executing - 1;
				uint8_t enc = ARENA(vm, proc->pc + 1);
				ft_bzero(&d, sizeof(d));
				proc->step = decode(&d, &g_op_tab[opi], enc);
				bool loaded = decode_load(&d, &g_op_tab[opi], vm->arena, proc);
				if (loaded)
					g_instruction_dispatch[opi](vm, proc, &d);
				proc->pc += proc->step;
				proc->executing = NONE;
				proc->execute_cycle += 1;
			}
			else
			{
				uint8_t op = ARENA(vm, proc->pc);
				if (op > 0 && op < 17)
				{
					proc->executing = op;
					proc->execute_cycle = vm->cycle + (g_op_tab[op - 1].cycles - 1);
				}
				else
				{
					proc->pc += 1;
					proc->execute_cycle = vm->cycle + 1;
				}
			}
			proc = proc->next;
		}
		if (vm->cycle >= vm->check_cycle)
			process_check(vm, &vm->processes);
	}
}
