/*
** EPITECH PROJECT, 2024
** fork
** File description:
** title
*/

#include <endian.h>
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

    addr = read_int16(arena, program->program_counter + 1);
    addr = htobe16(addr);
    addr = program->program_counter + addr % IDX_MOD;
    arena->programs = my_realloc(arena->programs,
        sizeof(program_t) * (arena->programs_count + 1),
        sizeof(arena_t) * arena->programs_count);
    my_memcpy(&arena->programs[arena->programs_count],
        sizeof(program_t), &arena->programs[arena->programs_count + 1]);
    arena->programs_count++;
    arena->programs[arena->programs_count - 1].program_counter = addr;
    return 0;
}

int execute_lfork(arena_t *arena, program_t *program)
{
    int16_t addr = 0;

    addr = read_int16(arena, program->program_counter + 1);
    addr = htobe16(addr);
    addr = program->program_counter + addr;
    arena->programs = my_realloc(arena->programs,
        sizeof(program_t) * (arena->programs_count + 1),
        sizeof(arena_t) * arena->programs_count);
    my_memcpy(&arena->programs[arena->programs_count],
        sizeof(program_t), &arena->programs[arena->programs_count + 1]);
    arena->programs_count++;
    arena->programs[arena->programs_count - 1].program_counter = addr;
    return 0;
}
