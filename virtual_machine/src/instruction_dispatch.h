#ifndef INSTRUCTION_DISPATCH_H
# define INSTRUCTION_DISPATCH_H
# include "virtual_machine.h"

typedef void			t_instruction(uint8_t *arena, t_process *p);

extern t_instruction	*g_instruction_dispatch[16];

#endif
