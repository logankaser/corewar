#include <assert.h>
#include "instruction_dispatch.h"

void no_op(uint8_t *a, t_process *p){(void)a;(void)p;assert(false);};

t_instruction		*g_instruction_dispatch[16] = {
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
	no_op,
};