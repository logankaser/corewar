#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H

/*
** Virtual machine state that processes do not need.
*/

typedef struct s_vm {

} t_vm;

/*
** Arena, AKA shared memory.
*/

typedef struct s_arena {

} t_arena;

/*
** Process specific memory.
*/

typedef struct s_process {

} t_process;

typedef void t_instruction(t_arena *a, t_process *p);

t_instruction *g_insturction_jmp_table[16] = {

};

#endif
