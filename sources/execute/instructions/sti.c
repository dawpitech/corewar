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
    uint32_t a;
    uint32_t b;

    if (infos == NULL)
        return 1;
    a = infos->params[1].value;
    b = infos->params[2].value;
    write_bytes(program->registers[infos->params[0].value - 1], 4,
                tmp + (a +
                b) % IDX_MOD, arena);
    free(infos);
    return 0;
}
