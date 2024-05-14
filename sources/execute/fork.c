/*
** EPITECH PROJECT, 2024
** fork
** File description:
** title
*/

#include <endian.h>
#include <stdint.h>
#include <stdlib.h>
#include "corewar.h"
#include "my.h"
#include "op.h"

static void *my_realloc(void *ptr, size_t new_size, size_t old_size)
{
    void *new_ptr;

    if (ptr == NULL)
        return malloc(new_size);
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;
    my_memcpy(ptr, old_size, new_ptr);
    free(ptr);
    return new_ptr;
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
    arena->programs[arena->programs_count - 1].program_counter = addr;
    arena->programs[arena->programs_count - 1].name =
        my_strdup(arena->programs[id].name);
    arena->programs[arena->programs_count - 1].cycles_before_die =
        CYCLE_TO_DIE;
    arena->programs[arena->programs_count - 1].size = arena->programs[id].size;
    arena->programs[arena->programs_count - 1].id = arena->programs[id].id;
    my_memcpy(&arena->programs[arena->programs_count - 1],
        REG_NUMBER * sizeof(int32_t), arena->programs[id].registers);
    return 0;
}

int execute_lfork(arena_t *arena, program_t *program)
{
    int16_t addr = 0;
    int id = program->id;

    arena->programs_count++;
    addr = read_int16(arena, program->program_counter + 1);
    addr = program->program_counter + htobe16(addr);
    arena->programs = my_realloc(arena->programs,
        sizeof(program_t) * (arena->programs_count),
        sizeof(program_t) * arena->programs_count - 1);
    my_memset(&arena->programs[arena->programs_count - 1], 0,
        sizeof(program_t));
    arena->programs[arena->programs_count - 1].program_counter = addr;
    arena->programs[arena->programs_count - 1].name =
        my_strdup(arena->programs[id].name);
    arena->programs[arena->programs_count - 1].cycles_before_die =
        CYCLE_TO_DIE;
    arena->programs[arena->programs_count - 1].size = arena->programs[id].size;
    my_memcpy(&arena->programs[arena->programs_count - 1],
        REG_NUMBER * sizeof(int32_t), arena->programs[id].registers);
    return 0;
}
