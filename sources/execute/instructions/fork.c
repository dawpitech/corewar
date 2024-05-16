/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <endian.h>

#include "corewar.h"
#include "my.h"
#include "op.h"

static
void update_arena_programs(const arena_t *arena, int16_t addr, int id)
{
    arena->programs[arena->programs_count - 1].program_counter = addr;
    arena->programs[arena->programs_count - 1].name =
        my_strdup(arena->programs[id].name);
    arena->programs[arena->programs_count - 1].cycles_before_die =
        CYCLE_TO_DIE;
    arena->programs[arena->programs_count - 1].size = arena->programs[id].size;
    arena->programs[arena->programs_count - 1].id = id;
}

int execute_fork(arena_t *arena, program_t *program)
{
    int16_t addr = 0;
    int id = program->id;

    arena->programs_count++;
    addr = read_int16(arena, program->program_counter + 1);
    addr = program->program_counter + htobe16(addr) % IDX_MOD;
    arena->programs = my_realloc(arena->programs,
        sizeof(program_t) * (arena->programs_count),
        sizeof(program_t) * (arena->programs_count - 1));
    my_memset(&arena->programs[arena->programs_count - 1], 0,
        sizeof(program_t));
    arena->programs[id].program_counter = (arena->programs[id].program_counter
        + 1 + IND_SIZE) % MEM_SIZE;
    update_arena_programs(arena, addr, id);
    my_memcpy(arena->programs[arena->programs_count - 1].registers, REG_NUMBER
        * sizeof(int32_t), arena->programs[id].registers);
    arena->programs[arena->programs_count - 1].cycles_before_next_instruction =
        arena->programs[id].cycles_before_next_instruction;
    return 0;
}
