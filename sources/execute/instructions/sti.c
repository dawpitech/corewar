/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <malloc.h>

#include "corewar.h"

int execute_sti(arena_t *arena, program_t *program)
{
    uint32_t tmp = program->program_counter;
    instruct_infos_t *infos = decode_instruction(arena,
        &program->program_counter);

    if (infos == NULL)
        return 1;
    write_bytes(program->registers[infos->params[0].value - 1], 4,
                tmp + (infos->params[1].value +
                infos->params[2].value) % IDX_MOD, arena);
    free(infos);
    return 0;
}
