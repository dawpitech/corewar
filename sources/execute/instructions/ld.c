/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <endian.h>
#include <malloc.h>

#include "corewar.h"

int execute_ld(arena_t *arena, program_t *program)
{
    uint32_t tmp = program->program_counter;
    uint32_t val = 0;
    instruct_infos_t *params = decode_instruction(arena,
        &program->program_counter);

    if (params == NULL)
        return 1;
    val = read_uint32(arena, tmp + params->params[0].value % IDX_MOD);
    val = htobe32(val);
    if (params->params[0].size == T_IND)
        val = params->params[0].value;
    program->registers[params->params[1].value - 1] = (int) val;
    program->carry_bit = 1;
    free(params);
    return 0;
}
