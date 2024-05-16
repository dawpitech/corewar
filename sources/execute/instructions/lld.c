/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <malloc.h>
#include <endian.h>

#include "corewar.h"
#include "op.h"

int execute_lld(arena_t *arena, program_t *program)
{
    uint32_t tmp = program->program_counter;
    uint32_t val = 0;
    instruct_infos_t *params = decode_instruction(arena,
        &program->program_counter);

    if (params == NULL || (params->params[1].value - 1) >= REG_SIZE)
        return 1;
    val = read_uint32(arena, tmp + params->params[0].value);
    val = htobe32(val);
    if (params->params[0].size == T_IND)
        val = params->params[0].value;
    program->registers[params->params[1].value - 1] = val;
    program->carry_bit = 1;
    free(params);
    return 0;
}
