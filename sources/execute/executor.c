/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** executor header
*/

#include "corewar.h"

static
int execute_live(arena_t *arena, program_t *program)
{
    uint8_t prog_id;

    program->program_counter += 1;
    prog_id = read_uint32(arena, program->program_counter + 1);
    if (prog_id > MAX_ARGS_NUMBER)
        return EXIT_FAILURE_TECH;
    program->program_counter += 4;
    arena->programs[prog_id].cycles_before_die = CYCLE_TO_DIE;
    return EXIT_SUCCESS_TECH;
}

static
int execute_ld(arena_t *arena, program_t *program)
{

}

int execute_next_inst(arena_t *arena, program_t *program)
{
    switch (arena->ram[program->program_counter]) {
        case 1:
            return execute_live(arena, program);
        case 2:
            return execute_ld(arena, program);
        default:
            return EXIT_FAILURE_TECH;
    }
    return EXIT_SUCCESS_TECH;
}
