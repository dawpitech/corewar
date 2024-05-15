/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <malloc.h>

#include "corewar.h"

static
void sub_init_a_b_values(const program_t *program,
    const instruct_infos_t *infos, int32_t *a, int32_t *b)
{
    (*a) = program->registers[infos->params[0].value - 1];
    (*b) = program->registers[infos->params[1].value - 1];
}

int execute_sub(arena_t *arena, program_t *program)
{
    instruct_infos_t *infos = decode_instruction(arena,
        &program->program_counter);
    int32_t a;
    int32_t b;
    int32_t and_result;

    if (infos == NULL || infos->params[2].size != T_REG ||
        infos->params[2].value > REG_NUMBER)
        return 1;
    sub_init_a_b_values(program, infos, &a, &b);
    and_result = a - b;
    if (and_result == 0)
        program->carry_bit = 1;
    program->registers[infos->params[2].value - 1] = and_result;
    free(infos);
    return 0;
}
