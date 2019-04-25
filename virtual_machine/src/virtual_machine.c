#include "virtual_machine.h"

void				vm_init(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
}

void				vm_del(t_vm *vm)
{
	unsigned i;

	i = 0;
	while (i < vm->player_count)
		free(vm->players[i++]);
}