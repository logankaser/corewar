#include "virtual_machine.h"

void				vm_init(t_vm *vm)
{
	vm->cycle = 0;
	vm->dump_cycle = 0;
	ft_vector_init(&vm->players);
	ft_bzero(&vm->arena, MEM_SIZE);
}

void				vm_del(t_vm *vm)
{
	unsigned i;

	i = 0;
	while (i < vm->players.length)
	{
		free(((t_player*)vm->players.data[i])->processes.data);
		++i;
	}
	ft_vector_del(&vm->players);
}