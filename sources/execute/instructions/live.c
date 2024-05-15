/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <endian.h>
#include <stdint.h>

#include "corewar.h"
#include "my_printf.h"
#include "op.h"

int execute_live(arena_t *arena, program_t *program)
{
    uint32_t prog_id;

    program->program_counter += 1;
    prog_id = read_uint32(arena, program->program_counter);
    prog_id = htobe32(prog_id);
    if (prog_id >= MAX_ARGS_NUMBER)
        return EXIT_FAILURE_TECH;
    program->program_counter += 4;
    arena->programs[prog_id].cycles_before_die = arena->cycle_to_die;
    my_printf("The player %d(%s) is alive.\n", prog_id,
        arena->programs[prog_id].name);
    arena->live_nbr++;
    if (arena->live_nbr == NBR_LIVE) {
        arena->cycle_to_die -= CYCLE_DELTA;
	arena->live_nbr = 0;
    }
    return EXIT_SUCCESS_TECH;
}
