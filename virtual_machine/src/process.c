#include "process.h"

t_process *process_spawn(t_vm *vm, t_process *parent, unsigned pc)
{
	t_process *new_process;

	new_process = ft_memalloc(sizeof(t_process));
	if (parent)
	{
		ft_memcpy(new_process, parent, sizeof(t_process));
	}
	new_process->pc = pc;
	new_process->executing = NONE;
	new_process->execute_cycle = vm->cycle + 1;
	new_process->next = vm->processes;
	vm->processes = new_process;
	return (new_process);
}
